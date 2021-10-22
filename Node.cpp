#include "Node.hpp"
#include <math.h>

Node::Node(Node * p, int pMove, int pPlayer) {
    parent = p;
    previousMove = pMove;
    previousPlayer = pPlayer;
}

Node::Node() {
    parent = nullptr;
    previousMove = -1;
    previousPlayer = 1;
}


void Node::CreateChildren(GameBoard * b) {
    if (childrenAdded) {
        return;
    }

    for(int i: b->GetValidMoves()) {
        children.push_back(new Node(this, i, b->GetPlayerToMove()));
    }
}


int Node::GetPreviousMove() {
    return previousMove;
}

float Node::UCT(float c) {
    if (n == 0) {
        return 0;
    }
    return w / n + c * sqrt( log(parent->n) / n );
}

Node::~Node() {
    DeleteChildren();
}

void Node::DeleteChildren() {
    children.clear();
}

bool Node::HasChildren() {
    return childrenAdded;
}

void Node::Backpropagate(int r) {

    // Update counter variables
    n += 1;
    if (r == previousPlayer) {
        w += 1;
    }

    if (parent) {
        parent->Backpropagate(r);
    }
}

int Node::GetPreviousPlayer() {
    return previousPlayer;
}

Node * Node::SelectChild(float c) {
    float bestUCT = -1;
    float newUTC;
    Node * bestChild;

    for(Node * child : children) {
        newUTC = child->UCT(c);
        if (newUTC > bestUCT) {
            bestUCT = newUTC;
            bestChild = child;
        }
    }

    return bestChild;
}