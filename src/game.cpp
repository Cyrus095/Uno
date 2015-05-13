#include <iostream>  // std::cout, std::cin, std::endl
#include <limits>    // std::numeric_limits
#include "game.hpp"

#define RESHUFFLE 200  // Number of times to shuffle Deck after reforming it

// Minimum function
static int minimum(int a, int b);

/*-----------------------------------------------------------*/

Game::Game(uint numPlayers)
{
    // Initialize each Player
    for (uint i = 0; i < numPlayers; i++) {
        std::string name;

        std::cout << "Type in Player " << (i + 1) << "'s name: ";
        std::getline(std::cin, name);
        Player *player = new Player(name);

        for (uint j = 0; j < INIT_HAND; j++) {
            player->addCard(deck.draw());
        }

        players.push_back(player);
    }

    // Add a non-effect Card to the Table
    while (true) {
        Card *card = deck.draw();

        if (card->getValue() > NINE) {
            deck.insert(card);
        }
        else {
            table.add(card);
            break;
        }
    }
}

/*-----------------------------------------------------------*/

Game::~Game()
{
    for (uint i = 0; i < players.size(); i++) {
        delete players.at(i);
    }

    players.clear();
}

/*-----------------------------------------------------------*/

void Game::play()
{
    for (turnCount = 0; true; ) {
        Player *current = players.at(turnCount);
        uint action = readTurn(current);

        if (action == 0) {
            draw(current);
        }
        else {
            // Plays selected card
            Card *card = current->getCard(action - 1);
            playCard(current, action);

            // Checks if current Player won
            if (checkVictory(current)) {
                break;
            }

            // Checks played card for special effect
            cardEffect(card);
        }

        turnCount = (turnCount + 1*clockwise) % players.size();

        // Prompt for continue before advancing to next Player
        std::cout << std::endl << std::endl;
        std::cout << "Press Enter to continue... " << std::flush;
        std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
        std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
    }
}

/*-----------------------------------------------------------*/

uint Game::readTurn(Player *current)
{
    uint action;

    system("clear");

    // Displays game's overall info
    std::cout << "TABLE CARD: ";
    table.getTop()->print();
    if (wild != COLOR_MAX) {
        std::cout << "[Wild = " << colorToStr(wild) << "]" << std::endl;
    }

    std::cout << "(Game order: ";
    if (clockwise == 1) {
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
    std::cout << "=== " << current->getName() << "'s turn! ===" << std::endl;
    if (current->size() == 1) {
        std::cout << " -> UNO! You have only one card left!" << std::endl;
    }
    std::cout << "Your hand:" << std::endl;
    current->print();

    std::cout << std::endl;
    std::cout << "Type a number to play the card if possible." << std::endl;
    std::cout << "Type '0' to draw card(s)." << std::endl;

    do {
        std::cout << ">> ";
        std::cin >> action;
    } while (action != 0 and
           (action > current->size() or not validMove(current->getCard(action - 1))));

    std::cout << std::endl;
    return action;
}

/*-----------------------------------------------------------*/

bool Game::validMove(Card *played)
{
    Card *top = table.getTop();

    if (drawCount > 1 and played->getValue() == DRAW_TWO and wild == COLOR_MAX) {
        return true;
    }
    else if (drawCount == 1 and
            (played->getColor() == top->getColor() or
            played->getColor() == wild or
            played->getValue() == top->getValue() or
            played->getValue() >= WILD)) {
                return true;
    }

    return false;
}

/*-----------------------------------------------------------*/

void Game::draw(Player *current)
{
    uint trueDraw = minimum(drawCount, deck.size() + table.size() - 1);

    // Displays message of cards drawed
    std::cout << current->getName() << " drew " << trueDraw << " card";
    if (trueDraw > 1) {
        std::cout << "s";
    }
    std::cout << "!" << std::endl;

    // Draw if there are Cards in Table (excluding the topmost one) or Deck
    for (uint i = 0; i < drawCount and trueDraw > 0; i++) {
        if (deck.size() == 0) {
            reformDeck();
        }
        Card *card = deck.draw();
        card->print();
        current->addCard(card);
    }

    // Resets draw counter
    drawCount = 1;
}

/*-----------------------------------------------------------*/

void Game::reformDeck()
{
    while (table.size() > 1) {
        deck.insert(table.removeEnd());
    }
    deck.shuffle(RESHUFFLE);
}

/*-----------------------------------------------------------*/

void Game::playCard(Player *current, uint position)
{
    Card *card = current->removeCard(position - 1);

    std::cout << current->getName() << " plays a ";
    card->print();

    // Adds the Card to the Table
    table.add(card);
}

/*-----------------------------------------------------------*/

bool Game::checkVictory(Player *current)
{
    if (current->size() <= 0) {
        std::cout << "### " << current->getName() << " wins! ###" << std::endl;
        return true;
    }

    return false;
}

/*-----------------------------------------------------------*/

void Game::cardEffect(Card *card)
{
    switch (card->getValue()) {
        case REVERSE:
            wild = COLOR_MAX;
            clockwise *= -1;
            if (players.size() == 2) {
                // Works as a SKIP when there are only two players
                turnCount = (turnCount + clockwise) % players.size();
            }
            std::cout << "Order has been reversed!" << std::endl;
            break;

        case SKIP:
            wild = COLOR_MAX;
            turnCount = (turnCount + clockwise) % players.size();
            std::cout << players.at(turnCount)->getName();
            std::cout << " was skipped!" << std::endl;
            break;

        case DRAW_TWO:
            wild = COLOR_MAX;
            if (drawCount == 1) {
                drawCount++;
            }
            else {
                drawCount += 2;
            }
            break;

        case WILD:
            chooseWild();
            break;

        case WILD_FOUR:
            if (drawCount == 1) {
                drawCount += 3;
            }
            else {
                drawCount += 4;
            }
            chooseWild();
            break;

        default:
            drawCount = 1;
            wild = COLOR_MAX;
            break;
    }
}

/*-----------------------------------------------------------*/

void Game::chooseWild() {
    uint value;

    std::cout << "Which color would you like?" << std::endl;
    for (Color c = COLOR_BEGIN; c < COLOR_MAX; c++) {
        std::cout << (int) (c + 1) << " = " << colorToStr(c) << "  ";
    }
    std::cout << std::endl;

    do {
        std::cout << ">> ";
        std::cin >> value;
        wild = (Color) (value - 1);
    } while (wild < RED or wild > BLUE);
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
