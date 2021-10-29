#include "MCTS.hpp"

#include <chrono>

MCTS::MCTS(GameBoard* b) { SetUpSearch(b); };

MCTS::MCTS() {
  GameBoard g = GameBoard();
  SetUpSearch(&g);
};

void MCTS::SetUpSearch(GameBoard* g) {
  game.CopyBoard(g);

  rootNode = new Node();
  rootNode->CreateChildren(&game);
}

void MCTS::MakeMove(int m) {
  Node* newRoot;
  for (Node* child : rootNode->children) {
    if (child->GetPreviousMove() != m) {
      // delete child;
    } else {
      newRoot = child;
    }
  }
  rootNode = newRoot;
  game.MakeMove(rootNode->GetPreviousMove());
}

void MCTS::DisplayBoard() { game.DisplayBoard(); }

int MCTS::FindBestMove() {
  int bestValue = -1;
  int bestMove = 0;
#ifdef profile
  std::cout << "N VALUES\n";
  std::cout << rootNode->children.size() << "\n";
#endif

  for (Node* child : rootNode->children) {
    if (child->n > bestValue) {
      bestValue = child->n;
      bestMove = child->GetPreviousMove();
    }

#ifdef profile
    std::cout << child->n << " " << child->w << " " << child->UCT(0.5) << "\n";
#endif
  }

  return bestMove;
}

void MCTS::RunSimulations(int num) {
#ifdef profile
  std::vector<std::chrono::microseconds> selection;
  std::vector<std::chrono::microseconds> expansions;
  std::vector<std::chrono::microseconds> simulation;
  std::vector<std::chrono::microseconds> backpropagation;
#endif

  for (size_t i = 0; i < num; i++) {
    Node* currentNode = rootNode;
    workingGame.CopyBoard(&game);

#ifdef profile
    auto start = std::chrono::high_resolution_clock::now();
#endif

    // Selection
    while (currentNode->HasChildren()) {
      // Use ~SQRT(2) as c value
      currentNode = currentNode->SelectChild(1.4142);
      workingGame.MakeMove(currentNode->GetPreviousMove());
    }

#ifdef profile
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    selection.push_back(duration);
#endif

    // Check if game is over
    if (workingGame.GameStatus() == 0) {
// Expansion
#ifdef profile
      auto start = std::chrono::high_resolution_clock::now();
#endif

      currentNode->CreateChildren(&workingGame);
      currentNode = currentNode->SelectChild(1.4142);

#ifdef profile
      auto end = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::microseconds>(end - start);
      expansions.push_back(duration);
      start = std::chrono::high_resolution_clock::now();
#endif

      // Simulation
      workingGame.MakeMove(currentNode->GetPreviousMove());
      int randomResult = FinishGameRandomly(&workingGame);

#ifdef profile
      end = std::chrono::high_resolution_clock::now();
      duration =
          std::chrono::duration_cast<std::chrono::microseconds>(end - start);
      simulation.push_back(duration);
#endif

      // Backpropagation
      currentNode->Backpropagate(randomResult);

    } else {
      currentNode->Backpropagate(workingGame.GameStatus());
    }
  }

#ifdef profile

  int selectionAvg = 0;

  for (auto i : selection) {
    selectionAvg += i.count();
  }

  selectionAvg /= selection.size();

  std::cout << "Selection took on average " << selectionAvg
            << " microseconds.\n";

  int expansionAvg = 0;

  for (auto i : expansions) {
    expansionAvg += i.count();
  }

  expansionAvg /= expansions.size();

  std::cout << "Expansion took on average " << expansionAvg
            << " microseconds.\n";

  int simulationAvg = 0;

  for (auto i : simulation) {
    simulationAvg += i.count();
  }

  simulationAvg /= simulation.size();

  std::cout << "Simulation took on average " << simulationAvg
            << " microseconds.\n";

#endif
}

int FinishGameRandomly(GameBoard* g) {
  // TODO: Make new GetValidMoves() that writes to a bitset and then pick
  // randomly from that bitset Probably fast than creating a new vector every
  // time

#ifdef profile
  std::vector<std::chrono::microseconds> getMoves;
#endif

  int moves[81];
  int count = 0;
  int numMoves = 0;

  while (g->GameStatus() == 0) {
#ifdef profile
    auto start = std::chrono::high_resolution_clock::now();
#endif

    count = g->GetValidMovesToArray(&moves[0]);

    // Make a random move
    int move = moves[rand() % count];

    g->MakeMoveFast(move);

#ifdef profile
    auto end = std::chrono::high_resolution_clock::now();
    numMoves++;
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    getMoves.push_back(duration);
#endif
  }

#ifdef profile
  int getMoveAvg = 0;

  for (auto i : getMoves) {
    getMoveAvg += i.count();
  }

  getMoveAvg /= getMoves.size();

  std::cout << "Getting moves took on average " << getMoveAvg << " "
            << getMoves.size() << " microseconds to find " << numMoves
            << " moves.\n";
#endif

  return g->GameStatus();
}

bool MCTS::ValidMove(int m) { return game.ValidMove(m); }

int MCTS::GetGameStatus() { return game.GameStatus(); };

int MCTS::GetRequiredBoard() { return game.GetRequiredBoard(); };

int MCTS::GetToMove() {
  if (game.GetXToMove()) {
    return 1;
  }

  return 2;
};

int MCTS::GetSpotStatus(int s) { return game.GetSpotStatus(s); };

int MCTS::GetMiniboardStatus(int b) { return game.GetMiniboardStatus(b); };