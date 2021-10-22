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

  tree.RunSimulations(1);

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