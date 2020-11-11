#pragma once
#include <stdio.h>
#include "defs.h"
#include "Board.h"
#include "BitboardProcessor.h"
#include "MakeMove.h"
#include "MoveGenerator.h"

class Perft
{
private:
	long leafNodes;
	MoveGenerator moveGenarator;
	MakeMove makeMove;

public:
	void ResetState();
	void ExecPerft(int depth, S_BOARD* pos, Board board, BitboardProcessor bitboardProc);
	void ExecPerfTest(int depth, S_BOARD* pos, Board board, BitboardProcessor bitboardproc);
};

