#include <iostream>

#include "GameBoard.hpp"
#include "MCTS.hpp"
#include "Node.hpp"

int main() {
  std::cout << "Working!\n";
  GameBoard b;

  b.Reset();

  MCTS tree = MCTS(&b);

  tree.SetUpSearch(&b);

  b.MakeMove(0);
  b.MakeMove(10);
  b.MakeMove(1);
  b.MakeMove(11);

  b.DisplayBoard();

  b.MakeMove(2);

  b.DisplayBoard();

  std::cout << " DONE \n";

  tree.RunSimulations(10000);

  // while(b.GameStatus() == 0) {

  //   int board, piece;

  //   std::cout << "ENTER BOARD\n";
  //   std::cin >> board;

  //   std::cout << "ENTER PIECE\n";
  //   std::cin >> piece;

  //   b.MakeMove(board * 9 + piece);
  //   tree.MakeMove(board * 9 + piece);

  //   b.DisplayBoard();

  //       tree.RunSimulations(10000);
  //   int move = tree.FindBestMove();

  //   tree.MakeMove(move);
  //   b.MakeMove(move);
  //   b.DisplayBoard();
  // }

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

  return (0);
}