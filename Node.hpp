#include <vector>
#include "GameBoard.hpp"

class Node {
    private:
        /**
         * Pointer to the parent that created this node.
         */
        Node * parent;

        /**
         * Pointers to all the children of this node. Represent all possible
         * moves from this position.
         */
        std::vector<Node *> children;

        /**
         * The move that was taken on the previous node to get to his node. A
         * game can be recreated by making the moves on the nodes of the tree.
         * 
         * Must be between 0 and 80 inclusive.
         */
        int previousMove;

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
         */
        Node(Node * p, int pMove);

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
         * @param c The exploration parameter
         * @return The UCT value
         */
        float UCT(float c);
};