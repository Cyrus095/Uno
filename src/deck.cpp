#include <cstdlib>         // uint, srand()
#include <ctime>           // time()
#include "deck.hpp"
#include "randomizer.hpp"
#include <iostream>

#define INIT_SHUFFLE 1000

/*-----------------------------------------------------------*/

Deck::Deck(bool init)
{
    srand(time(NULL));

    if (init) {
        // Cards from ONE to DRAW_TWO
        for (Value v = ONE; v < WILD; v++) {
            for (Color c = COLOR_BEGIN; c < COLOR_MAX; c++) {
                dq.push_front(new Card(c, v));
                dq.push_front(new Card(c, v));
            }
        }

        // ZERO, WILD and WILD_FOUR cards
        for (Color c = COLOR_BEGIN; c < COLOR_MAX; c++) {
            dq.push_front(new Card(c, ZERO));
            dq.push_front(new Card(COLOR_MAX, WILD));
            dq.push_front(new Card(COLOR_MAX, WILD_FOUR));
        }

        shuffle(INIT_SHUFFLE);
    }
}

/*-----------------------------------------------------------*/

Deck::~Deck()
{
    while (not dq.empty()) {
        Card *card = dq.front();
        dq.pop_front();
        delete card;
    }

    dq.clear();
}

/*-----------------------------------------------------------*/

uint Deck::size()
{
    return dq.size();
}

/*-----------------------------------------------------------*/

Card * Deck::draw()
{
    Card *card = NULL;

    if (not dq.empty()) {
        card = dq.front();
        dq.pop_front();
    }

    return card;
}

/*-----------------------------------------------------------*/

void Deck::insert(Card *card)
{
    dq.push_back(card);
}

/*-----------------------------------------------------------*/

void Deck::reverse()
{
    uint s = dq.size();

    for (uint i = 0; i < s; i++) {
        insert(draw());
    }
}

/*-----------------------------------------------------------*/

void Deck::print()
{
    for (uint i = 0; i < dq.size(); i++) {
        dq.at(i)->print();
    }
}

/*-----------------------------------------------------------*/

void Deck::shuffle(uint times)
{
    if (not dq.empty()) {
        for (uint i = 0; i < times; i++) {
            int pos = randInt(0, dq.size() - 1);

            Card *card = dq.at(pos);
            dq.erase(dq.begin() + pos);
            dq.push_back(card);
        }
    }
}
