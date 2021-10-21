#include "GameBoard.hpp"

GameBoard::GameBoard() {
    Reset();
};


void GameBoard::MakeMove(int move) {
    // Save board state to the history
    previousMoves[movesCompleted] = move;

    for (size_t i = 0; i < 9; i++) {
        previousValidBoards[9 * movesCompleted + i] = validBoards[i];
    }
    
    // Make the move
    if (xToMove) {
        board[move * 2] = 1; 
    }

    else {
        board[move * 2 + 1] = 1;
    }

    // Keep miniboardStatues updated
    int targetBoard = (int) move / 9;
    miniboardStatuses[targetBoard] = CheckMiniboardStatusByNumber(targetBoard);

    // Update valid boards
    validBoards.reset();

    int newRequiredBoard = (int) (move % 9) / 2;
    if (miniboardStatuses[newRequiredBoard] != 0) {
        // Any open board is valid
        for (size_t i = 0; i < 8; i++) {

            if (miniboardStatuses[i] == 0) {
                validBoards[i] = 1;
            }
        }
    }

    else {
        // Only the target board is valid
        validBoards[newRequiredBoard] = 1;
    }

    // Update move counter
    movesCompleted += 1;
    xToMove = !xToMove;
};


bool GameBoard::ValidMove(int move) {
    int targetBoard = (int) move / 9;

    // Check board is valid
    if (!validBoards[targetBoard]) {
        return false;
    }

    // Check space is empty
    return !board[move * 2] && !board[move * 2 + 1];
}


void GameBoard::UnmakeMove() {
    movesCompleted -= 1;

    // Empty the space
    board[previousMoves[movesCompleted] * 2] = 0;
    board[previousMoves[movesCompleted] * 2 + 1] = 0;

    // Update the miniboard statuses
    int targetBoard = (int) previousMoves[movesCompleted] / 9;
    miniboardStatuses[targetBoard] = CheckMiniboardStatusByNumber(targetBoard);

    // Copy the valid boards back
    for (size_t i = 0; i < 8; i++)
    {
        validBoards[i] = previousValidBoards[movesCompleted * 9 + i];
    }
    
    xToMove = !xToMove;
}

void GameBoard::CopyBoard(GameBoard *b) {
    xToMove = b->xToMove;
    movesCompleted = b->movesCompleted;

    memcpy(&previousMoves, &(b->previousMoves), sizeof(previousMoves));
    memcpy(&previousValidBoards, &(b->previousValidBoards), sizeof(previousValidBoards));
    memcpy(&miniboardStatuses, &(b->miniboardStatuses), sizeof(miniboardStatuses));
    memcpy(&board, &(b->board), sizeof(board));
    memcpy(&validBoards, &(b->validBoards), sizeof(validBoards));
};

void GameBoard::Reset() {
    board.reset();
    validBoards.set();

    xToMove = true;
    movesCompleted = 0;
    memset(&miniboardStatuses, 1, sizeof(miniboardStatuses));
};

int GameBoard::CheckMiniboardStatusByNumber(int b) {
    std::bitset<18> miniboard;

    for (size_t i = 0; i < 18; i++)
    {
        miniboard[i] = board[b * 18 + i];
    }
    
    return CheckMiniboardStatus(&miniboard);
}

int CheckMiniboardStatus(std::bitset<18> *miniboard) {
    // Check if winning for x
    std::bitset<18> mask;

    // Check for x winning
    for (size_t i = 0; i < 8; i++) {
        mask = *miniboard;
        mask &= winningForX[i];

        if (mask == winningForX[i]) {
            return 1;
        }
    }
    
    // Check for o winning
    for (size_t i = 0; i < 8; i++) {
        mask = *miniboard;
        mask &= winningForO[i];
        
        if (mask == winningForO[i]) {
            return 2;
        }
    }
    
    // Check for filled board
    std::bitset<9> spaces;

    for (size_t i = 0; i < 9; i++) {
        spaces[i] = (*miniboard)[i * 2] || (*miniboard)[i * 2 + 1];
    };
    
    if (spaces == fullBoard) {
        return -1;
    }
    
    return 0;
};

int GameBoard::GameStatus() {
    // Represent the states of all the games miniboards as one board
    std::bitset<18> miniboard;

    miniboard.reset();

    for (size_t i = 0; i < 9; i++)
    {
        if (miniboardStatuses[i] == 1) {
            miniboard[i * 2] = 1;
        }

        else if (miniboardStatuses[i] == 2) {
            miniboard[i * 2 + 1] = 1;
        }
    }
    
    return CheckMiniboardStatus(&miniboard);
};

bool GameBoard::GetXToMove() {
    return xToMove;
};


int GameBoard::GetSpotStatus(int s) {
    if (board[s * 2]) {
        return 1;
    }

    else if (board[s * 2 + 1]) {
        return 2;
    }

    return 0;
};