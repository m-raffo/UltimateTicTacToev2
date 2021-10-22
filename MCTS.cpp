#include "MCTS.hpp"
#include <chrono>

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
            // delete child;
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
    std::cout << "N VALUES\n";
    std::cout << rootNode->children.size() <<  "\n";

    for (Node * child : rootNode->children) {
        if (child->n > bestValue) {
            bestValue = child->n;
            bestMove = child->GetPreviousMove();
        }

                    std::cout << child-> n << " " << child->w << " " << child->UCT(0.5) << "\n";

    }

    return bestMove;
}

void MCTS::RunSimulations(int num) {

    std::vector<std::chrono::microseconds> selection;
    std::vector<std::chrono::microseconds> expansions;
    std::vector<std::chrono::microseconds> simulation;
    std::vector<std::chrono::microseconds> backpropagation;

    for (size_t i = 0; i < num; i++) {

        Node * currentNode = rootNode;
        workingGame.CopyBoard(&game);

        auto start = std::chrono::high_resolution_clock::now();

        // Selection
        while(currentNode->HasChildren()) {
            // Use ~SQRT(2) as c value
            currentNode = currentNode->SelectChild(1.4142);
            workingGame.MakeMove(currentNode->GetPreviousMove());
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        selection.push_back(duration);

        // Check if game is over
        if (workingGame.GameStatus() == 0) {

            // Expansion
            auto start = std::chrono::high_resolution_clock::now();

            currentNode->CreateChildren(&workingGame);
            currentNode = currentNode->SelectChild(1.4142);

            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            expansions.push_back(duration);

            start = std::chrono::high_resolution_clock::now();

            // Simulation
            workingGame.MakeMove(currentNode->GetPreviousMove());
            int randomResult = FinishGameRandomly(&workingGame);

            end = std::chrono::high_resolution_clock::now();

            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            simulation.push_back(duration);


            // Backpropagation
            currentNode->Backpropagate(randomResult);
        } else {
            currentNode->Backpropagate(workingGame.GameStatus());
        }
    }

    int selectionAvg = 0;

    for(auto i: selection) {
        selectionAvg += i.count();
    }

    selectionAvg /= selection.size();

    std::cout << "Selection took on average " << selectionAvg << " microseconds.\n";

    int expansionAvg = 0;

    for(auto i: expansions) {
        expansionAvg += i.count();
    }

    expansionAvg /= expansions.size();

    std::cout << "Expansion took on average " << expansionAvg << " microseconds.\n";

    int simulationAvg = 0;

    for(auto i: simulation) {
        simulationAvg += i.count();
    }

    simulationAvg /= simulation.size();

    std::cout << "Simulation took on average " << simulationAvg << " microseconds.\n";


}

int FinishGameRandomly(GameBoard * g) {
    // TODO: Make new GetValidMoves() that writes to a bitset and then pick randomly from that bitset
    // Probably fast than creating a new vector every time
    std::vector<std::chrono::microseconds> getMoves;
    int moves[81];
    int count = 0;
    int numMoves = 0;
    while (g->GameStatus() == 0) {

        auto start = std::chrono::high_resolution_clock::now();
        count = g->GetValidMovesToArray(&moves[0]);

        // Make a random move
        int move = moves[rand() % count];
        
        g->MakeMoveFast(move);

        auto end = std::chrono::high_resolution_clock::now();


        numMoves++;


        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        getMoves.push_back(duration);

        

    }

    int getMoveAvg = 0;

    for(auto i: getMoves) {
        getMoveAvg += i.count();
    }

    // getMoveAvg /= getMoves.size();

    // std::cout << "Getting moves took on average " << getMoveAvg << " " << getMoves.size() << " microseconds to find "<< numMoves << " moves.\n";


    return g->GameStatus();
}