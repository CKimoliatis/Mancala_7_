#include "Mancala7.h"

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

    Board(Player *p1, Player *p2) {
        vector<int> temp(15, 4);
        cells = temp;
        cells[14] = 0;
        cells[7] = 0;
        player1 = p1;
        player2 = p2;
        gameOverFlag = false;
    }

    bool getGameStatus() {
        return gameOverFlag;
    }

    void playerTwoMove(int &currCell) {
        int play;
        cout << player2->getName() << "'s Turn. Enter a number 1 - 6 (L to R)" << endl;
        play = 1 + (rand() % 6);
        play = 14 - play;
        while (cells[play] == 0) {
            play = 1 + (rand() % 6);
            play = 14 - play;
        }
        currCell = play + 1;

        int marbles = cells[play]; //Gets the marbles in the played cell
        cells[play] = 0; //Set the played cell to 0

        for (currCell; marbles; currCell++) { //Loop through all subsequent cells
            if (currCell % 7) {
                cells[(currCell % 14)]++;
                marbles--;
            } else if (currCell % 14 == 0) {
                cells[14]++;
                marbles--;
            }
        }
        currCell--;
    }

    void checkTwoMove(int &currCell, int &playerTurn) {
        if (8 <= currCell && currCell <= 13 && cells[currCell] == 1 && cells[14 - currCell] > 0) {
            cout << endl;
            cout << "Capture!" << endl;
            cells[14] += (1 + cells[14 - currCell]);
            cells[14 - currCell] = 0;
            cells[currCell] = 0;
            playerTurn = 1;
        } else if (currCell == 14) {
            cout << endl;
            cout << "You have earned another turn, go again." << endl;
        } else {
            playerTurn = 1;
        }
    }

    void checkOneMove(int &currCell, int &playerTurn) {
        if (1 <= currCell && currCell <= 6 && cells[currCell] == 1 && cells[14 - currCell] > 0) { //Check in range
            cout << endl;
            cout << "Capture!" << endl;
            cells[7] += (1 + cells[14 - currCell]); //Add to score bank the capture
            cells[14 - currCell] = 0; //Set captured pit to 0
            cells[currCell] = 0; //Set captee pit to 0
            playerTurn = 2;
        } else if (currCell == 7) { //Check if landed on score bank
            cout << endl;
            cout << "You have earned another turn, go again." << endl;
        } else { //Else change turns
            playerTurn = 2;
        }
    }

    void playerOneMove(int &currCell) {
        int play;
        cout << player1->getName() << "'s Turn. Enter a number 1 - 6 (L to R)" << endl;
        cin>>play;

        currCell = play + 1;
        int marbles = cells[play]; //Gets the marbles in the played cell
        cells[play] = 0; //Set the played cell to 0

        for (currCell; marbles; currCell++) { //Loop through all subsequent cells and ++
            currCell = currCell % 14; //Mod in case play has enough marbs to loop thru
            if (currCell != 0) { //If currCell != 0 means we are not on enemy score bank
                cells[(currCell % 14)]++;
                marbles--;
            }
        }
        currCell--;
    }

    void printBoard() {
        cout << " " << cells[13] << "|" << cells[12] << "|" << cells[11] << "|" << cells[10] << "|"
                << cells[9] << "|" << cells[8] << endl;
        cout << cells[14] << "===========" << cells[7] << endl;
        cout << " " << cells[1] << "|" << cells[2] << "|" << cells[3] << "|" << cells[4] << "|"
                << cells[5] << "|" << cells[6] << endl;
    }

    void accumulateFinalPoints() {
        cells[14] += cells[13] + cells[12] + cells[11] + cells[10] + cells[9] + cells[8];
        cells[7] += cells[1] + cells[2] + cells[3] + cells[4] + cells[5] + cells[6];
        for (int i = 1; i <= 6; i++) {
            cells[i] = 0;
        }
        for (int j = 8; j <= 13; j++) {
            cells[j] = 0;
        }
    }

    void gameOver() {
        if ((cells[13] + cells[12] + cells[11] + cells[10] + cells[9] + cells[8] == 0) ||
                (cells[1] + cells[2] + cells[3] + cells[4] + cells[5] + cells[6] == 0)
                && (counter != 0)) {

            accumulateFinalPoints();
            player1->setPoints(cells[7]);
            player2->setPoints(cells[14]);

            if (player1->getPoints() > player2->getPoints()) {
                player1->setWin(1);
                player2->setLoss(1);
            } else {
                player2->setWin(1);
                player1->setLoss(1);
            }
            counter++;
            gameOverFlag = true;
        }
        counter++;
    }
};

int Board::counter = 0;
#endif /* BOARD_H_ */
