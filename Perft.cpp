#include "Perft.h"


void Perft::ExecPerfTest(int depth, S_BOARD* pos, Board board, BitboardProcessor bitboardproc)
{
	ASSERT(board.CheckBoard(pos, bitboardproc));

	if(depth == 0)
	{
		leafNodes++;
		return;
	}

	S_MOVELIST list[1];
	moveGenarator.GenerateAllMoves(pos,bitboardproc, list, board);

	int MoveNum = 0;
	for(MoveNum=0; MoveNum < list->count; ++MoveNum)
	{
		if (!makeMove.MakeMoveOnBoard(pos, list->moves[MoveNum].move, bitboardproc, board))
			continue;
	}
}

