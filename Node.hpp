#pragma once
#include <vector>
#include "GameBoard.hpp"

class Node {
    private:
        /**
         * Pointer to the parent that created this node.
         */
        Node * parent;

        /**
         * The move that was taken on the previous node to get to his node. A
         * game can be recreated by making the moves on the nodes of the tree.
         * 
         * Must be between 0 and 80 inclusive.
         */
        int previousMove;

        /**
         * The player that took the previous move.
         * 1 is X and 2 is O.
         */
        int previousPlayer;

        /**
         * True if children have been added. False otherwise.
         */
        bool childrenAdded = false;

    public:
        /**
         * Node construtor.
         * 
         * @param p Pointer to the parent of this node
         * @param pMove The move taken to get to this node
         * @param pPlayer The player that took the last move
         */
        Node(Node * p, int pMove, int pPlayer);

        /**
         * Node construtor for the root node. There is no parent and no previous move.
         */
        Node();

        /**
         * Node destructor.
         */
        ~Node();

        /**
         * Creates and adds children to the node. One child is created for
         * every valid move on the given gameboard.
         * 
         * Children can only be created once. If called more than once, nothing happens.
         * 
         * @param b The current gameboard
         */
        void CreateChildren(GameBoard * b);

        /**
         * The number of wins for the player to move from the given position.
         */
        int w = 0;

        /**
         * The number of times the position has been considered.
         */
        int n = 0;

        /**
         * Calculate the UCT value for the current node.
         * 
         * @warning Calling this function on a node with no parent causes undefined
         * behavior.
         * 
         * @param c The exploration parameter
         * @return The UCT value
         */
        float UCT(float c);

        /**
         * Find the child node with the highest UCT value.
         * 
         * @param c The exploration parameter
         * @return Pointer to the selected child
         */
        Node * SelectChild(float c);

        /**
         * Pointers to all the children of this node. Represent all possible
         * moves from this position.
         */
        std::vector<Node *> children;

        /**
         * Get the move that was taken on the previous node to get to his node. A
         * game can be recreated by making the moves on the nodes of the tree.
         * 
         * Must be between 0 and 80 inclusive.
         */
        int GetPreviousMove();

        /**
         * Deletes all of its children recursively from memory.
         */
        void DeleteChildren();

        /**
         * Checks if the node has children already.
         * 
         * @return True if it has children, False otherwise
         */
        bool HasChildren();

        /**
         * Backpropagate the given result through the tree.
         * 
         * @param r The result. 1 for X win, 2 for O win, -1 for tie
         */
        void Backpropagate(int r);

        /**
         * Get the player who took the previous move.
         * 
         * @return The player who took the last move, 1 is X and 2 is O.
         */
        int GetPreviousPlayer();
};