#include <iostream>  // std::cout, std::cin, std::endl
#include <limits>    // std::numeric_limits
#include "game.hpp"

#define RESHUFFLE 200  // Number of times to shuffle Deck after reforming it

// Minimum function
static int minimum(int a, int b);

/*-----------------------------------------------------------*/

Game::Game(bool init)
{
    deck = new Deck(init);
    table = new Table();

    if (init) {
        // Add a non-effect Card to the Table
        while (true) {
            Card *card = deck->draw();

            if (card->getValue() > NINE) {
                deck->insert(card);
            }
            else {
                table->add(card);
                break;
            }
        }
    }
}

/*-----------------------------------------------------------*/

Game::~Game()
{
    delete deck;
    delete table;
}

/*-----------------------------------------------------------*/

void Game::initPlayer(Player *player)
{
    for (uint i = 0; i < INIT_HAND; i++) {
        player->addCard(deck->draw());
    }
}

/*-----------------------------------------------------------*/

void Game::play(Player *player)
{
    if (gameOver) {
        return;
    }

    if (skipped) {
        skipped = false;
        return;
    }

    uint action = readTurn(player);

    if (action == 0) {
        draw(player);
    }
    else {
        // Plays selected card
        Card *card = player->getCard(action - 1);
        playCard(player, action);

        // Checks if current Player won
        if (player->handSize() <= 0) {
            gameOver = true;
        }

        // Checks played card for special effect
        cardEffect(card);
    }

    // Prompt for continue before advancing to next Player
    std::cout << std::endl << std::endl;
    std::cout << "Press Enter to continue... " << std::flush;
    std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
    std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
}

/*-----------------------------------------------------------*/

void Game::setSkip(bool skipped)
{
    this->skipped = skipped;
}

/*-----------------------------------------------------------*/

void Game::setGameOver(bool gameOver)
{
    this->gameOver = gameOver;
}

/*-----------------------------------------------------------*/

void Game::setDrawCount(uint drawCount)
{
    this->drawCount = drawCount;
}

/*-----------------------------------------------------------*/

void Game::setReverse(bool reversed)
{
    this->reversed = reversed;
}

/*-----------------------------------------------------------*/

void Game::setDeck(Deck *d)
{
    delete this->deck;
    deck = d;
}

/*-----------------------------------------------------------*/

void Game::setTable(Table *t)
{
    delete this->table;
    table = t;
}

/*-----------------------------------------------------------*/

bool Game::checkSkip()
{
    return skipped;
}

/*-----------------------------------------------------------*/

bool Game::checkGameOver()
{
    return gameOver;
}

/*-----------------------------------------------------------*/

uint Game::getDrawCount()
{
    return drawCount;
}

/*-----------------------------------------------------------*/

bool Game::checkReverse()
{
    return reversed;
}

/*-----------------------------------------------------------*/

Deck * Game::getDeck()
{
    return deck;
}

/*-----------------------------------------------------------*/

Table * Game::getTable()
{
    return table;
}

/*-----------------------------------------------------------*/

uint Game::readTurn(Player *player)
{
    uint action;

    system("clear");

    // Displays game's overall info
    std::cout << "TABLE CARD: ";
    table->getTop()->print();

    std::cout << "(Game order: ";
    if (reversed) {
        std::cout << ">>)" << std::endl;
    }
    else {
        std::cout << "<<)" << std::endl;
    }

    if (drawCount > 1) {
        std::cout << "Draw 2 stack: +" << drawCount << std::endl;
        std::cout << std::endl;
    }

    // Displays Player's info
    std::cout << std::endl;
    std::cout << "=== " << player->getName() << "'s turn! ===" << std::endl;
    if (player->handSize() == 1) {
        std::cout << " -> UNO! You have only one card left!" << std::endl;
    }
    std::cout << "Your hand:" << std::endl;
    player->print();

    std::cout << std::endl;
    std::cout << "Type a number to play the card if possible." << std::endl;
    std::cout << "Type '0' to draw card(s)." << std::endl;

    do {
        std::cout << ">> ";
        std::cin >> action;
    } while (action != 0 and
           (action > player->handSize() or not validMove(player->getCard(action - 1))));

    std::cout << std::endl;
    return action;
}

/*-----------------------------------------------------------*/

bool Game::validMove(Card *played)
{
    Card *top = table->getTop();

    if (drawCount > 1 and played->getValue() == DRAW_TWO) {
        return true;
    }
    else if (drawCount == 1 and
            (played->getColor() == top->getColor() or
            played->getValue() == top->getValue() or
            played->getValue() >= WILD)) {
                return true;
    }

    return false;
}

/*-----------------------------------------------------------*/

void Game::draw(Player *player)
{
    uint trueDraw = minimum(drawCount, deck->size() + table->size() - 1);

    // Displays message of cards drawed
    std::cout << player->getName() << " drew " << trueDraw << " card";
    if (trueDraw > 1) {
        std::cout << "s";
    }
    std::cout << "!" << std::endl;

    // Draw if there are Cards in Table (excluding the topmost one) or Deck
    for (uint i = 0; i < drawCount and trueDraw > 0; i++) {
        if (deck->size() == 0) {
            reformDeck();
        }
        Card *card = deck->draw();
        card->print();
        player->addCard(card);
    }

    // Resets draw counter
    drawCount = 1;
}

/*-----------------------------------------------------------*/

void Game::reformDeck()
{
    while (table->size() > 1) {
        deck->insert(table->removeEnd());
    }
    deck->shuffle(RESHUFFLE);
}

/*-----------------------------------------------------------*/

void Game::playCard(Player *player, uint position)
{
    Card *card = player->removeCard(position - 1);

    std::cout << player->getName() << " plays a ";
    card->print();

    // Adds the Card to the Table
    table->add(card);
}

/*-----------------------------------------------------------*/

void Game::cardEffect(Card *card)
{
    switch (card->getValue()) {
        case REVERSE:
            reversed = not reversed;
            std::cout << "Order has been reversed!" << std::endl;
            break;

        case SKIP:
            skipped = true;
            break;

        case DRAW_TWO:
            if (drawCount == 1) {
                drawCount++;
            }
            else {
                drawCount += 2;
            }
            break;

        case WILD:
            card->setColor(chooseWild());
            break;

        case WILD_FOUR:
            if (drawCount == 1) {
                drawCount += 3;
            }
            else {
                drawCount += 4;
            }
            card->setColor(chooseWild());
            break;

        default:
            drawCount = 1;
            break;
    }
}

/*-----------------------------------------------------------*/

Color Game::chooseWild() {
    Color color;

    std::cout << "Which color would you like?" << std::endl;
    for (Color c = COLOR_BEGIN; c < COLOR_MAX; c++) {
        std::cout << (int) (c + 1) << " = " << colorToStr(c) << "  ";
    }
    std::cout << std::endl;

    do {
        uint value;
        std::cout << ">> ";
        std::cin >> value;
        color = (Color) (value - 1);
    } while (color < RED or color > BLUE);

    return color;
}

/*-----------------------------------------------------------*/

Game& Game::operator =(Game a)
{
    Deck *deck = new Deck();

    while (a.getDeck()->size() > 0) {
        deck->insert(a.getDeck()->draw());
    }
    deck->reverse();

    Table *table = new Table();
    while (a.getTable()->size() > 0) {
        table->add(a.getTable()->removeEnd());
    }

    this->setDeck(deck);
    this->setTable(table);

    this->skipped   = a.checkSkip();
    this->reversed  = a.checkReverse();
    this->drawCount = a.getDrawCount();
    this->gameOver  = a.checkGameOver();

    return *this;
}

/*-----------------------------------------------------------*
 *
 * Returns the minimum between 'a' and 'b'.
 *
 */
static int minimum(int a, int b)
{
    return (a <= b ? a : b);
}
