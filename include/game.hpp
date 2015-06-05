#pragma once

#include "deck.hpp"
#include "table.hpp"
#include "player.hpp"

#define INIT_HAND 7  // Beginning number of Cards for each Player

/*-----------------------------------------------------------*
 *
 *  Class where the game is actually played.
 *
 */

class Game
{
    private:
        // Basic parameters
        Deck *deck;
        Table *table;

        // Game-specific parameters
        bool skipped    = false;  // If 'true', Player will have his turn skipped
        bool reversed   = true;   // Flag for playing order
        uint drawCount  = 1;      // Draw 2 and Draw 4 stacking
        bool gameOver   = false;  // Flag is 'true' if a Player already won

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
        Color chooseWild();

    public:
        // Initializes the Game with the specified number of players
        Game(bool init = false);

        // Clears memory used by Game
        ~Game();

        // Gives a fixed number of cards to the specified Player
        void initPlayer(Player *player);

        // Makes the specified Player have his turn
        void play(Player *player);

        // Prints information regarding the Game
        void print();

        // Checks if next Player will be skipped
        bool checkSkip();

        // Returns 'true' if somebody has already won the Game
        bool checkGameOver();

        // Returns current draw card stack
        uint getDrawCount();

        // Returns if a Reverse card's effect is active
        bool checkReverse();

        /* 
         * -------------------------------------
         *  Below methods are to be used only
         *  for Packet sending and receiving!
         * -------------------------------------
         */

        // Sets the 'skipped' parameter
        void setSkip(bool skip);

        // Sets the 'gameOver' parameter
        void setGameOver(bool gameOver);

        // Sets the 'drawCount' parameter
        void setDrawCount(uint drawCount);

        // Sets the 'reversed' parameter
        void setReverse(bool reverse);

        // Deletes current Deck, replacing it with the argument
        void setDeck(Deck *deck);

        // Deletes current Table, replacing it with the argument
        void setTable(Table *table);

        // Returns current Deck
        Deck * getDeck();

        // Returns current Table
        Table * getTable();

        Game& operator =(Game game);
};

// Operators for SFML Packets
sf::Packet& operator <<(sf::Packet& packet, Game& game);
sf::Packet& operator >>(sf::Packet& packet, Game& game);
