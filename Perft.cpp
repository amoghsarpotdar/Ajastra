#include "Perft.h"


void Perft::ExecPerfTest(int depth, S_BOARD* pos, Board board, BitboardProcessor bitboardproc)
{
	ASSERT(board.CheckBoard(pos, bitboardproc));
	board.PrintBoard(pos);

	printf("\nStarting test to Depth:%d\n", depth);
	
	leafNodes = 0;
	S_MOVELIST list[1];
	moveGenarator.GenerateAllMoves(pos,bitboardproc, list, board);
	int move;
	int MoveNum = 0;
	for(MoveNum=0; MoveNum < list->count; ++MoveNum)
	{
		move = list->moves[MoveNum].move;
		if (!makeMove.MakeMoveOnBoard(pos, move, bitboardproc, board)) {
			continue;
		}
		long cumnodes = leafNodes;
		ExecPerfTest(depth - 1, pos, board, bitboardproc);
		makeMove.ReverseMoveOnBoard(pos, bitboardproc, board);
		long oldnodes = leafNodes - cumnodes;
		//printf("Move %d: %s : %ld\n", MoveNum + 1, PrMove(move), oldnodes);
	}
	printf("\nTest complete : %ld nodes visited\n", leafNodes);
}

