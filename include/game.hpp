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
        bool skipped    = false;  // If 'true', Player will have turn skipped when playing
        bool reversed   = true;   // For Reverse Card
        uint drawCount  = 1;      // For draw-type Cards
        bool gameOver   = false;  // Used for checking if a Player already won

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

        void setSkip(bool skip);

        void setGameOver(bool gameOver);

        void setDrawCount(uint drawCount);

        void setReverse(bool reverse);

        void setDeck(Deck *d);

        void setTable(Table *t);

        // Checks if next Player will be skipped
        bool checkSkip();

        // Returns 'true' if somebody has already won the Game
        bool checkGameOver();

        // Returns current draw card stack
        uint getDrawCount();

        // Returns if a Reverse card's effect is active
        bool checkReverse();

        // Returns current Deck
        Deck * getDeck();

        // Returns current Table
        Table * getTable();

        Game& operator =(Game a);
};
