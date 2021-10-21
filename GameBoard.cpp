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

BoardCoords AbsoluteIndexToBoardAndPiece(int i) {
    BoardCoords result;

    // i = index
    // gx = global x value (independent of board)
    // gy = same
    // lx = local x value (within board)
    // ly = same
    // bx = x value of the whole board
    // by = same
    // pi = piece index
    // bi = board index

    int gx, gy, lx, ly, bx, by, pi, bi;

    gx = i % 9;
    gy = i / 9;

    lx = gx % 3;
    ly = gy % 3;

    bx = (i % 9) / 3;
    by = i / 27;

    pi = ly * 3 + lx;
    bi = by * 3 + bx;

    result.board = bi;
    result.piece = pi;

    return result;
}


void GameBoard::DisplayBoard() {

    if (xToMove) {
        std::cout << "X to move\n";
    } else {
        std::cout << "O to move\n";
    }

    int requiredBoard = GetRequiredBoard();
    if (requiredBoard != -1) {
        std::cout << "Required board: " << requiredBoard << '\n';
    } else {
        std::cout << "Required board: None\n";
    }

    int absolutePieceIndex, location;
    BoardCoords coords;

    for (int row = 0; row < 9; row++) {
        for (int boardRow = 0; boardRow < 3; boardRow++) {

            for (int col = 0; col < 3; col++) {
                absolutePieceIndex = (row * 9) + (boardRow * 3) + col;
                coords = AbsoluteIndexToBoardAndPiece(absolutePieceIndex);
                location = 2 + (2 * coords.piece);
                int spotStatus = GetSpotStatus(absolutePieceIndex);
                if (spotStatus == 1) {
                    std::cout << "\033[31mX\033[0m";
                } else if (spotStatus == 2) {
                    std::cout << "\033[94mO\033[0m";
                } else {
                    std::cout << " ";
                }

                // Give a divider if not on the last one
                if (col != 2) {
                    std::cout << " | ";
                }
                

            }

            std::cout << "\\\\ ";

        }

        if ((row + 1) % 3 != 0){
            std::cout << "\n---------   ---------   ---------   \n";
        } else {
            std::cout << "\n=================================\n";
        }

    }
}

int GameBoard::GetRequiredBoard() {
    int requiredBoard = -1;

    for (size_t i = 0; i < 9; i++) {
        if (validBoards[i]) {
            if (requiredBoard == -1) {
                requiredBoard = i;
            } else {
                // There is no required board, as more than 1 board has been marked as valid
                return -1;
            }
        }
    }

    return requiredBoard;
}