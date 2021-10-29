import cython


cdef class PyMCTS:
    cdef GameBoard c_gameboard
    cdef MCTS c_mcts


    def __cinit__(self):
        self.c_gameboard = GameBoard()
        self.c_mcts = MCTS(cython.address(self.c_gameboard))


    def display(self):
        self.c_gameboard.DisplayBoard()


    def validMove(self, move):
        assert type(move) == int
        assert 0 <= move <= 80

        return self.c_gameboard.ValidMove(move)


    def makeMove(self, move):
        assert type(move) == int
        assert 0 <= move <= 80

        self.c_gameboard.MakeMove(move)
        self.c_mcts.MakeMove(move)


    def runSimulations(self, sims):
        assert type(sims) == int
        self.c_mcts.RunSimulations(sims)

    
    def findBestMove(self):
        return self.c_mcts.FindBestMove()


    def makeBestMove(self):
        best = self.c_mcts.FindBestMove()
        self.makeMove(best)


    def getGameStatus(self):
        return self.c_gameboard.GameStatus()


    def getRequiredBoard(self):
        return self.c_gameboard.GetRequiredBoard()


    def checkMiniboard(self, board):
        assert type(board) == int
        assert 0 <= board <= 8

        return self.c_gameboard.GetMiniboardStatus(board)


    def getSpot(self, spot):
        assert type(spot) == int
        assert 0 <= spot <= 80

        return self.c_gameboard.GetSpotStatus(spot)


    def display2(self):
        self.c_gameboard.DisplayBoard()
        self.c_mcts.DisplayBoard()


    @property
    def x_to_move(self):
        return self.c_gameboard.GetXToMove()



