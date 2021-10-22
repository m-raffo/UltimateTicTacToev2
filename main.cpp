#include "GameBoard.hpp"
#include <iostream>
#include "Node.hpp"
#include "MCTS.hpp"

int main() {
  std::cout << "Working!\n";
  GameBoard b;

  b.Reset();

  MCTS tree = MCTS(&b);

  tree.SetUpSearch(&b);

  while(b.GameStatus() == 0) {
    tree.RunSimulations(10000);
    int move = tree.FindBestMove();

    tree.MakeMove(move);
    b.MakeMove(move);
    b.DisplayBoard();

    int board, piece;

    std::cout << "ENTER BOARD\n";
    std::cin >> board;

    std::cout << "ENTER PIECE\n";
    std::cin >> piece;

    b.MakeMove(board * 9 + piece);
    std::cout << "B MAKD\n";
    tree.MakeMove(board * 9 + piece);
    std::cout << "TERE MAKD\n";

    b.DisplayBoard();
  }


  // Node a = Node();

  // b.MakeMove(1);

  // b.MakeMove(12);

  // b.MakeMove(30);

  // b.MakeMove(13);

  // b.MakeMove(37);

  // b.MakeMove(14);


  // a.CreateChildren(&b);


  // for (Node * i: a.children) {
  //   std::cout << "Making move " << i->GetPreviousMove() << "\n";
  //   b.MakeMove(i->GetPreviousMove());
  //   b.DisplayBoard();

  //   b.UnmakeMove();
  // }

  return(0);
}