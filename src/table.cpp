#include "table.hpp"

/*-----------------------------------------------------------*/

Table::~Table()
{
    while (not pile.empty()) {
        delete removeEnd();
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
    return pile.back();
}

/*-----------------------------------------------------------*/

Card * Table::removeEnd()
{
    Card *card = pile.front();
    pile.pop();

    return card;
}
