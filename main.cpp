#include "GameBoard.hpp"
#include <iostream>

int main() {
  std::cout << "Working!\n";
  GameBoard b;

  b.Reset();

  for (size_t i = 0; i < 81; i++) {
    b.MakeMove(i);
    b.DisplayBoard(); 
  }
  


  return(0);
}