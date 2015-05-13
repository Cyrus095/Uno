#pragma once

#include "deck.hpp"
#include "table.hpp"
#include "player.hpp"

#define INIT_HAND 7    // Beginning number of Cards for each Player

/*-----------------------------------------------------------*/

class Game
{
    private:
        // Basic parameters
        Deck deck;
        Table table;
        std::deque<Player *> players;

        // Game-specific parameters
        uint turnCount  = 0;      // Shows who's the current Player
        int clockwise   = 1;      // For Reverse Card
        uint drawCount  = 1;      // For draw-type Cards
        Color wild = COLOR_MAX;   // If equal to any Color, than a wild Card is on Table

        // Reads specified Player's action
        uint readTurn(Player *current);

        // Checks if the played Card is valid based on the Table's top Card
        bool validMove(Card *played);

        // Makes the specified Player draw cards equal to 'drawCount' counter
        void draw(Player *current);

        // Adds old Table cards to Deck, shuffling it afterwards
        void reformDeck();

        // Plays the Card in the specified position from the current Player's hand
        void playCard(Player *player, uint position);

        // Checks if specified Player won the game
        bool checkVictory(Player *current);

        // Activates an effect depending on the Card's Value
        void cardEffect(Card *card);

        // Asks the current Player to choose a Color for the played wild card
        void chooseWild();

    public:
        // Initializes the Game with the specified number of players
        Game(uint numPlayers);

        // Clears memory used by Game
        ~Game();

        // Plays the game until someone wins!
        void play();
};
