#include "GameBoard.hpp"
#include <iostream>
#include <assert.h>

int main() {
    std::cout << "Testing GameBoard...\n";

    GameBoard b;
    b.Reset();
    
    assert (b.GetXToMove());

    assert (b.ValidMove(0));
    assert (b.ValidMove(5));

    b.MakeMove(2);

    assert (b.GetSpotStatus(2) == 1);
    assert (b.GetSpotStatus(80) == 0);
    assert (!b.GetXToMove());

    b.MakeMove(10);

    assert (b.GetSpotStatus(2) == 1);
    assert (b.GetSpotStatus(10) == 2);
    assert (b.GetSpotStatus(12) == 0);

    assert (b.ValidMove(3));
    assert (!b.ValidMove(2));
    assert (!b.ValidMove(60));

    assert (b.GetXToMove());

    b.UnmakeMove();
    assert (b.GetSpotStatus(2) == 1);
    assert (b.GetSpotStatus(80) == 0);
    assert (b.GetSpotStatus(10) == 0);
    assert (!b.GetXToMove());

    // Test CopyBoard

    // Test GameStatus

    // Test CheckMiniboardStatusByNumber

    std::cout << "GameBoard passed all tests.\n";
    return 0;
}