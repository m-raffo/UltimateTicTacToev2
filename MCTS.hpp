#pragma once
#include "GameBoard.hpp"
#include "Node.hpp"

class MCTS {
 private:
  /**
   * The GameBoard that is used to process all of the moves.
   */
  GameBoard game;

  /**
   * The GameBoard that is used for computations, such as random game results.
   */
  GameBoard workingGame;

  /**
   * The start node of the search tree.
   */
  Node* rootNode;

 public:
  /**
   * Constructor for MCTS object.
   *
   * @param b The position to start the search from
   */
  MCTS(GameBoard* b);

  /**
   * Constructor for MCTS object.
   *
   * Starts with an empty board if no arguments given.
   */
  MCTS();

  /**
   * Set up the tree for a new search from the given position.
   *
   * @param g The position to start the search from
   */
  void SetUpSearch(GameBoard* g);

  /**
   * Run the given number of MCTS simulations.
   *
   * @param num The number of simulations to run.
   */
  void RunSimulations(int num);

  /**
   * Return the best move based on simulations completed.
   *
   * @return Move index
   */
  int FindBestMove();

  /**
   * Makes the given move.
   *
   * Narrows the tree, and unneeded parts are removed. Saves simulation data
   * continue with evaluation.
   *
   * @param m The move index to make
   */
  void MakeMove(int m);

  /**
   * Calls DisplayBoard() on the search tree's gameboard.
   */
  void DisplayBoard();

  /**
   * Check if the move is valid.
   *
   * @param m The move to theck. 0..80
   * @return True if valid, false otherwise
   */
  bool ValidMove(int m);

  /**
   * Gets the current status of the game.
   *
   * @return 1 for X win, 2 for O win, 0 for ongoing, -1 for tie
   */
  int GetGameStatus();

  /**
   * Gets the current required board, -1 if no required board.
   *
   * @return The board
   */
  int GetRequiredBoard();

  /**
   * Gets the current player to move.
   *
   * @return 1 for X to move, 2 for O to move
   */
  int GetToMove();

  /**
   * Gets the current status of a spot.
   *
   * @return 1 for taken by X, 2 for taken by O, 0 for open
   */
  int GetSpotStatus(int s);

  /**
   * Gets the status of a miniboard.
   *
   * @return 1 for1 for X win, 2 for O win, 0 for ongoing, -1 for tie
   */
  int GetMiniboardStatus(int b);
};

/**
 * Finishes the given game with random moves on both sides and returns the
 * result.
 *
 * @warning All of the data on the given gamebaord will be lost.
 * @return 1 if X wins, 2 if O wins, -1 if tie
 */
int FinishGameRandomly(GameBoard* g);