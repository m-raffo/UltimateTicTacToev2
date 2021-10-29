#pragma once
#include <bitset>
#include <iostream>
#include <vector>

const std::bitset<9> fullBoard = 0b111111111;

const std::bitset<18> winningForX[8] = {
    0b000000000000010101, 0b000000010101000000, 0b010101000000000000,
    0b000001000001000001, 0b000100000100000100, 0b010000010000010000,
    0b010000000100000001, 0b000001000100010000,
};

const std::bitset<18> winningForO[8] = {
    0b000000000000101010, 0b000000101010000000, 0b101010000000000000,
    0b000010000010000010, 0b001000001000001000, 0b100000100000100000,
    0b100000001000000010, 0b000010001000100000,
};

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
  int_fast8_t miniboardStatuses[9];

  /**
   * Updates the status of the given miniboard.
   *
   * @param b The miniboard to check. 0 <= b <= 8
   * @return 1 if won by X, 2 if won by O, 0 if ongoing, -1 if tie.
   */
  int UpdateMiniboardStatusByNumber(int b);

  /**
   * Updates the status of the given miniboard.
   *
   * This operation is performed faster than UpdateMiniboardStatusByNumber
   * because more information is given by the caller.
   *
   * @param b The miniboard to check. 0 <= b <= 8
   * @param p The player that played last. 1=X, 2=O
   * @return 1 in won by X, 2 if won by O, 0 if ongoing, -1 if tie.
   */
  int UpdateMiniboardStatusByNumberFast(int b, int p);

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
   * Makes a move quickly without saving necessary information to unmake
   * the move.
   *
   * @warning After moves have been made this way, UnmakeMove() should
   * not be called.
   *
   * @param move The move to make. Must be 0 <= move <= 80.
   */
  void MakeMoveFast(int move);

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

  /**
   * Gets the board that must be played on.
   * @return The id of the board, -1 if no required board
   */
  int GetRequiredBoard();

  /**
   * Gets all the valid moves.
   * @return A vector with each valid move as a value in range 0..81.
   */
  std::vector<int> GetValidMoves();

  /**
   * Writes all of the valid moves to the given array and returns the
   * number of valid moves written. Anything at the index returned and
   * after in the array is untouched.
   *
   * @param b Pointer to the array to write to, at least size 81
   * @return The number of moves written
   */
  int GetValidMovesToArray(int *b);

  /**
   * Get the current player to move.
   *
   * @return 1 for X, 2 for O
   */
  int GetPlayerToMove();

  /**
   * Stores which boards are valid to be played on by the current player.
   */
  std::bitset<9> validBoards;

  /**
   * Checks the status of the given miniboard.
   *
   * @param b The board to check in range 0..8.
   * @return The status of the board. 1=X win; 2=O win; 0=ongoing; -1=Tie
   */
  int GetMiniboardStatus(int b);
};

/**
 * Checks the status of the given miniboard.
 *
 * @param miniboard A pointer to the miniboard to check.
 * @return 1 if won by X, 2 if won by O, 0 if ongoing, -1 if tie.
 */
int EvaluateMiniboardStatus(std::bitset<18> *miniboard);

class BoardCoords {
 public:
  int board;
  int piece;
};

/**
 * Gets the board and piece index from an absolute index.
 * @param i The index to convert
 * @return The corresponding coordinates
 */
BoardCoords AbsoluteIndexToBoardAndPiece(int i);