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
        Node * rootNode;

    public:
        /**
         * Constructor for MCTS object.
         * 
         * @param b The position to start the search from
         */
        MCTS(GameBoard * b);

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
        void SetUpSearch(GameBoard * g);

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

};

/**
 * Finishes the given game with random moves on both sides and returns the result.
 * 
 * @warning All of the data on the given gamebaord will be lost.
 * @return 1 if X wins, 2 if O wins, -1 if tie
 */
int FinishGameRandomly(GameBoard * g);