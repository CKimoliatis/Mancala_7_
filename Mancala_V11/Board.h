#include "Mancala7.h"
#include "Player.h"

#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
    vector<int> cells;
    Player *player1;
    Player *player2;
    bool gameOverFlag;
    static int counter;

public:

    Board(Player *p1, Player *p2);

    bool getGameStatus();

    void playerTwoMove(int &currCell);

    void checkTwoMove(int &currCell, int &playerTurn);

    void checkOneMove(int &currCell, int &playerTurn);

    void playerOneMove(int &currCell);

    void printBoard();

    void accumulateFinalPoints();

    void gameOver();
};
#endif /* BOARD_H_ */
