# distutils: language = c++

from libcpp cimport bool


cdef extern from "GameBoard.cpp":
    pass


cdef extern from "GameBoard.hpp":
    cdef cppclass GameBoard:
        GameBoard() except +

        void MakeMove(int)
        void MakeMoveFast(int)
        bool ValidMove(int)
        void UnmakeMove()

        int GameStatus()
        void Reset()

        bool GetXToMove()
        int GetSpotStatus(int)
        int GetRequiredBoard()

        int GetPlayerToMove()

        void DisplayBoard()

        int GetMiniboardStatus(int)


cdef extern from "MCTS.cpp":
    pass


cdef extern from "Node.cpp":
    pass


cdef extern from "MCTS.hpp":
    cdef cppclass MCTS:
        MCTS(GameBoard * g) except +
        MCTS() except +

        void SetUpSearch(GameBoard * g)

        void RunSimulations(int)

        int FindBestMove()

        void MakeMove(int)

        void DisplayBoard()

