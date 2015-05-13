#include <iostream>    // std::cout
#include "player.hpp"

/*-----------------------------------------------------------*/

Player::Player(std::string name)
{
    this->name = name;
}

/*-----------------------------------------------------------*/

Player::~Player()
{
    for (uint i = 0; i < hand.size(); i++) {
        delete hand.at(i);
    }

    hand.clear();
}

/*-----------------------------------------------------------*/

uint Player::size()
{
    return hand.size();
}

/*-----------------------------------------------------------*/

void Player::print()
{
    for (uint i = 0; i < hand.size(); i++) {
        std::cout << (i+1) << ") ";
        hand.at(i)->print();
    }
}

/*-----------------------------------------------------------*/

void Player::addCard(Card *card)
{
    hand.push_back(card);
}

/*-----------------------------------------------------------*/

Card * Player::getCard(uint position)
{
    if (position > hand.size()) {
        return NULL;
    }

    return hand.at(position);
}

/*-----------------------------------------------------------*/

Card * Player::removeCard(uint position)
{
    Card *card = NULL;

    if (position <= hand.size()) {
        card = hand.at(position);
        hand.erase(hand.begin() + position);
    }

    return card;
}

/*-----------------------------------------------------------*/

std::string Player::getName()
{
    return name;
}
