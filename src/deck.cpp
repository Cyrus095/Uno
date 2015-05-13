#include <cstdlib>         // uint, srand()
#include <ctime>           // time()
#include "deck.hpp"
#include "randomizer.hpp"

#define INIT_SHUFFLE 1000

/*-----------------------------------------------------------*/

Deck::Deck()
{
    srand(time(NULL));

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
        dq.push_front(new Card(c, WILD));
        dq.push_front(new Card(c, WILD_FOUR));
    }

    shuffle(INIT_SHUFFLE);
}

/*-----------------------------------------------------------*/

Deck::~Deck()
{
    for (uint i = 0; i < dq.size(); i++) {
        delete dq.at(i);
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
    Card *draw = dq.front();
    dq.pop_front();

    return draw;
}

/*-----------------------------------------------------------*/

void Deck::insert(Card *card)
{
    dq.push_back(card);
}

/*-----------------------------------------------------------*/

void Deck::shuffle(uint times)
{
    for (uint i = 0; i < times; i++) {
        int pos = randInt(0, dq.size() - 1);

        Card *card = dq.at(pos);
        dq.erase(dq.begin() + pos);
        dq.push_back(card);
    }
}
