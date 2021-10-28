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

  b.MakeMove(0);
  b.MakeMove(10);
  b.MakeMove(1);
  std::cout << "FAST " << b.CheckMiniboardStatusByNumberFast(0, 1) << "\n";
  std::cout << "SLOW " << b.CheckMiniboardStatusByNumber(0) << "\n";

  b.MakeMove(11);

  b.DisplayBoard();

  b.MakeMove(2);

  std::cout << "FAST " << b.CheckMiniboardStatusByNumberFast(0, 1) << "\n";
  std::cout << "SLOW " << b.CheckMiniboardStatusByNumber(0) << "\n";


  b.DisplayBoard();


  std::cout <<" DONE \n";


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

  return(0);
}