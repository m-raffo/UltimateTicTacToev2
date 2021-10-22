#include "MCTS.hpp"

MCTS::MCTS(GameBoard * b) {
    game.CopyBoard(b);
};

void MCTS::SetUpSearch(GameBoard * g) {
    game.CopyBoard(g);

    rootNode = new Node();
    rootNode->CreateChildren(&game);
}

void MCTS::MakeMove(int m) {
    Node * newRoot;
    for(Node * child : rootNode->children) {
        if (child->GetPreviousMove() != m) {
            delete child;
        } else {
            newRoot = child;
        }
    }
    rootNode = newRoot;
    game.MakeMove(rootNode->GetPreviousMove());
}

int MCTS::FindBestMove() {
    int bestValue = -1;
    int bestMove = 0;
    for (Node * child : rootNode->children) {
        if (child->n > bestValue) {
            bestValue = child->n;
            bestMove = child->GetPreviousMove();
        }
    }

    return bestMove;
}

void MCTS::RunSimulations(int num) {

    for (size_t i = 0; i < num; i++) {

        std::cout << "Starting simulation.\n";

        Node * currentNode = rootNode;
        workingGame.CopyBoard(&game);

        std::cout << "Starting board...\n";
        workingGame.DisplayBoard();

        std::cout << "HAS CHILDREN " << currentNode->HasChildren();

        // Selection
        while(currentNode->HasChildren()) {
            std::cout << "Selecting board...";
            // Use ~SQRT(2) as c value
            currentNode = currentNode->SelectChild(1.4142);
            workingGame.MakeMove(currentNode->GetPreviousMove());

            std::cout << currentNode->GetPreviousMove() << "\n";
            workingGame.DisplayBoard();

        }

        std::cout << "Board without children reached\n";

        workingGame.DisplayBoard();


        // Check if game is over
        if (workingGame.GameStatus() == 0) {

            std::cout << "Game status: " << workingGame.GameStatus() << "\nExpanding now\n";

            // Expansion
            currentNode->CreateChildren(&workingGame);
            currentNode = currentNode->SelectChild(1.4142);

            std::cout << "New child selected.\n";
            workingGame.DisplayBoard();

            std::cout << "Random simulation...\n";

            // Simulation
            workingGame.MakeMove(currentNode->GetPreviousMove());
            int randomResult = FinishGameRandomly(&workingGame);
            std::cout << " RESULT " << randomResult << "\n";


            // Backpropagation
            currentNode->Backpropagate(randomResult);
        } else {
            currentNode->Backpropagate(workingGame.GameStatus());
        }
    }

}

int FinishGameRandomly(GameBoard * g) {
    std::cout << "Starting random simulation\n";
    while (g->GameStatus() == 0) {
        std::vector<int> moves = g->GetValidMoves();

        std::cout << "There are " << moves.size() << " moves\n";

        if (moves.size() == 0) {
            g->DisplayBoard();
            for(int i = 0; i < 9; i++) {
                std::cout << " VALID BOARD " << g->validBoards << "\n";
            }
            
        }

                    g->DisplayBoard();

        
        // Make a random move
        int move = moves[rand() % moves.size()];
        g->MakeMove(move);
        std::cout << "Made move " << (int)(move / 9) << " " << move % 9  << "\n";
    }

    return g->GameStatus();
}