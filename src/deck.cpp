#include <cstdlib>         // uint, srand()
#include <ctime>           // time()
#include "deck.hpp"
#include "randomizer.hpp"

#define INIT_SHUFFLE 1000

/*-----------------------------------------------------------*/

Deck::Deck(bool init)
{
    srand(time(NULL));

    if (init) {
        // Cards from ONE to DRAW_TWO
        for (Value v = ONE; v < WILD; v++) {
            for (Color c = COLOR_BEGIN; c < COLOR_MAX; c++) {
                deque.push_front(new Card(c, v));
                deque.push_front(new Card(c, v));
            }
        }

        // ZERO, WILD and WILD_FOUR cards
        for (Color c = COLOR_BEGIN; c < COLOR_MAX; c++) {
            deque.push_front(new Card(c, ZERO));
            deque.push_front(new Card(COLOR_MAX, WILD));
            deque.push_front(new Card(COLOR_MAX, WILD_FOUR));
        }

        shuffle(INIT_SHUFFLE);
    }
}

/*-----------------------------------------------------------*/

Deck::~Deck()
{
    while (not deque.empty()) {
        Card *card = deque.front();
        deque.pop_front();
        delete card;
    }

    deque.clear();
}

/*-----------------------------------------------------------*/

uint Deck::size()
{
    return deque.size();
}

/*-----------------------------------------------------------*/

Card * Deck::draw()
{
    Card *card = NULL;

    if (not deque.empty()) {
        card = deque.front();
        deque.pop_front();
    }

    return card;
}

/*-----------------------------------------------------------*/

void Deck::insert(Card *card)
{
    deque.push_back(card);
}

/*-----------------------------------------------------------*/

void Deck::reverse()
{
    uint s = deque.size();

    for (uint i = 0; i < s; i++) {
        insert(draw());
    }
}

/*-----------------------------------------------------------*/

void Deck::shuffle(uint times)
{
    if (not deque.empty()) {
        for (uint i = 0; i < times; i++) {
            int pos = randInt(0, deque.size() - 1);

            Card *card = deque.at(pos);
            deque.erase(deque.begin() + pos);
            deque.push_back(card);
        }
    }
}

/*-----------------------------------------------------------*/

sf::Packet& operator <<(sf::Packet& packet, Deck deck)
{
    packet << static_cast<sf::Uint32>(deck.size());

    while (deck.size() > 0) {
        packet << *deck.draw();
    }

    return packet;
}

/*-----------------------------------------------------------*/

sf::Packet& operator >>(sf::Packet& packet, Deck& deck)
{
    sf::Uint32 size;
    packet >> size;

    for (sf::Uint32 i = 0; i < size; i++) {
        Card *card = new Card();
        packet >> *card;
        deck.insert(card);
    }
    deck.reverse();

    return packet;
}
