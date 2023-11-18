#include "board.h"

// Constructor
Board::Board(const int score[][BOARD_SIZE]) : curPlayer(X), id(0) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cells[i][j] = EMPTY;
            this->score[i][j] = score[i][j];
        }
    }
}

// Check if the board is full
bool Board::isFull() const {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (cells[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

// Check if the game is finished
bool Board::isFinished() const {
    if (isFull()) {
        return true;
    }
    int boardScore = getBoardScore();
    if (boardScore == WIN_SCORE || boardScore == -WIN_SCORE) {
        return true;
    }
    return false;
}
// Calculate the board's current score
int Board::getBoardScore() const {
    int scoreX = 0;
    int scoreO = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        int rowSum = 0;
        int colSum = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            rowSum += score[i][j] * static_cast<int>(cells[i][j]);
            colSum += score[j][i] * static_cast<int>(cells[j][i]);
        }
        scoreX += std::max(0, rowSum) * getCellWeight(X);
        scoreO += std::max(0, -rowSum) * getCellWeight(O);
        scoreX += std::max(0, colSum) * getCellWeight(X);
        scoreO += std::max(0, -colSum) * getCellWeight(O);
    }
    int diagSum1 = 0;
    int diagSum2 = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        diagSum1 += score[i][i] * static_cast<int>(cells[i][i]);
        diagSum2 += score[i][BOARD_SIZE - i - 1] * static_cast<int>(cells[i][BOARD_SIZE - i - 1]);
    }
    scoreX += std::max(0, diagSum1) * getCellWeight(X);
    scoreO += std::max(0, -diagSum1) * getCellWeight(O);
    scoreX += std::max(0, diagSum2) * getCellWeight(X);
    scoreO += std::max(0, -diagSum2) * getCellWeight(O);
    if (scoreX == scoreO) {
        return 0;
    }
    return (curPlayer == X ? scoreX - scoreO : scoreO - scoreX);
}

// Play the next move at coords. If successful, update the data members and return true. Otherwise return false.
bool Board::play(const BoardCoordinate& coords) {
    if (!coords.isValid() || cells[coords.row][coords.col] != EMPTY) {
        return false;
    }

    cells[coords.row][coords.col] = curPlayer;

    // Update current player and calculate new ID
    curPlayer = (curPlayer == X) ? O : X;
    id = 0;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            int cellValue = 0;
            if (cells[row][col] == X) {
                cellValue = 1;
            } else if (cells[row][col] == O) {
                cellValue = 2;
            }
            id += cellValue * (pow(3, row * BOARD_SIZE + col));
        }
    }

    return true;
}

