#include <iostream>    // std::cout
#include "player.hpp"

/*-----------------------------------------------------------*/

Player::Player()
{
    this->name = "";
}

/*-----------------------------------------------------------*/

Player::Player(std::string name)
{
    this->name = name;
}

/*-----------------------------------------------------------*/

Player::~Player()
{
    while (not hand.empty()) {
        Card *card = hand.front();
        hand.pop_front();
        delete card;
    }

    hand.clear();
}

/*-----------------------------------------------------------*/

uint Player::handSize()
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

void Player::setName(std::string name)
{
    this->name = name;
}

/*-----------------------------------------------------------*/

std::string Player::getName()
{
    return name;
}
