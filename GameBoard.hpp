#include <iostream>
#include <bitset>

const std::bitset<18> winningForO[8] = {
    0b000000000000010101,
    0b000000010101000000,
    0b010101000000000000,
    0b000001000001000001,
    0b000100000100000100,
    0b010000010000010000,
    0b010000000100000001,
    0b000001000100010000,
};

const std::bitset<18> winningForX[8] = {
    0b000000000000101010,
    0b000000101010000000,
    0b101010000000000000,
    0b000010000010000010,
    0b001000001000001000,
    0b100000100000100000,
    0b100000001000000010,
    0b000010001000100000,
};

const std::bitset<9> fullBoard = 0b111111111;


class GameBoard {
    private:
        /**
         * Stores the current state of the board.
         * 
         * Each board is represented by 18 bits.
         * 
         * Each space in a board is represented by 2 bits.
         * There are 9 spaces in each board.
         * The first bit of the space represents if X have moved there.
         * The second bit represents if O has moved there.
         * 
         * There are 9 boards total.
         */
        std::bitset<162> board;


        /**
         * Stores which boards are valid to be played on by the current player.
         */
        std::bitset<9> validBoards;


        /**
         * True if X is the player to move on the board.
         */
        bool xToMove;


        /**
         * Stores all of the previous moves in chronological order they were
         * made in.
         */
        uint_fast8_t previousMoves[81];


        /**
         * Stores all of the valid boards for previous moves. This information
         * is necessary to be able to unmake moves.
         * 
         * Values are stored in sets of 9 in chronological order in which the
         * moves were made.
         */ 
        std::bitset<729> previousValidBoards;


        /**
         * Stores the number of moves completed.
         */
        uint_fast8_t movesCompleted;

        /**
         * Stores the statuses of the miniboards.
         */
        uint_fast8_t miniboardStatuses[9];

    public:

        /**
         * Default constructor. Starts game as an empty board.
         */
        GameBoard();
    
        /**
         * Makes the given move on the board. Note, the validity of the move
         * is not checked.
         * 
         * @param move The move to be made. Must be 0 <= move <= 80.
         */
        void MakeMove(int move);


        /**
         * Checks if a move is valid.
         * 
         * @param move The move to be checked.
         * @return True if the move is valid, False otherwise.
         */
        bool ValidMove(int move);


        /**
         * Undoes the most recent move made and restores the board to its
         * previous state.
         */
        void UnmakeMove();


        /**
         * Makes the board an exact copy of the given board. All information
         * stored in the board is lost.
         * 
         * @param b The board to be copied.
         */
        void CopyBoard(GameBoard *b);


        /**
         * Writes the current board to the console output.
         */
        void DisplayBoard();


        /**
         * Checks the status of the game currently.
         * 
         * @return 1 if X is the winner, 2 if O is the winner. 0 if the game is
         * ongoing. -1 if the game is a tie.
         */
        int GameStatus();


        /**
         * Resets the board back to the starting position. All information on the
         * board is lost.
         */
        void Reset();


        /**
         * Checks the status of the given miniboard.
         * 
         * @param b The miniboard to check. 0 <= b <= 8
         * @return 1 if won by X, 2 if won by O, 0 if ongoing, -1 if tie.
         */
        int CheckMiniboardStatusByNumber(int b); 

        /**
         * Gets the current player to move.
         * @return True if X to move, False otherwise
         */
        bool GetXToMove();

        /**
         * Gets the status of the given spot on the board.
         * @param s The spot to check. 0 <= s <= 80
         * @return 1 if space claimed by X, 2 if claimed by O, 0 if empty.
         */
        int GetSpotStatus(int s);

};


/**
 * Checks the status of the given miniboard.
 * 
 * @param miniboard A pointer to the miniboard to check.
 * @return 1 if won by X, 2 if won by O, 0 if ongoing, -1 if tie.
 */
int CheckMiniboardStatus(std::bitset<18> *miniboard);