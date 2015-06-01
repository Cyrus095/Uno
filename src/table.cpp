#include "table.hpp"

/*-----------------------------------------------------------*/

Table::~Table()
{
    while (not pile.empty()) {
        Card *card = pile.front();
        pile.pop();
        delete card;
    }
}

/*-----------------------------------------------------------*/

uint Table::size()
{
    return pile.size();
}

/*-----------------------------------------------------------*/

void Table::add(Card *card)
{
    return pile.push(card);
}

/*-----------------------------------------------------------*/

Card * Table::getTop()
{
    Card *card = NULL;

    if (not pile.empty()) {
        card = pile.back();
    }

    return card;
}

/*-----------------------------------------------------------*/

Card * Table::removeEnd()
{
    Card *card = NULL;

    if (not pile.empty()) {
        card = pile.front();
        pile.pop();
    }

    return card;
}
