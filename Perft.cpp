#include "Perft.h"

/// <summary>
/// Do not forget to call this function before executing ExecPerfTest.
/// This ensures all state variables are reset back to 0.
/// </summary>
void Perft::ResetState()
{
	leafNodes = 0;
}


void Perft::ExecPerfTest(int depth, S_BOARD* pos, Board board, BitboardProcessor bitboardproc)
{
	ASSERT(board.CheckBoard(pos, bitboardproc));
	board.PrintBoard(pos);
	printf("\nStarting test to Depth:%d\n", depth);
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
		//ExecPerfTest(depth - 1, pos, board, bitboardproc);
		ExecPerft(depth - 1, pos, board, bitboardproc);
		makeMove.ReverseMoveOnBoard(pos, bitboardproc, board);
		long oldnodes = leafNodes - cumnodes;
		//printf("Move %d: %s : %ld\n", MoveNum + 1, PrMove(move), oldnodes);
	}
	printf("\nTest complete : %ld nodes visited\n", leafNodes);
}

void Perft::ExecPerft(int depth, S_BOARD* pos, Board board, BitboardProcessor bitboardProc)
{
	ASSERT(board.CheckBoard(pos, bitboardProc));

	if(depth == 0)
	{
		leafNodes++;
		return;
	}

	S_MOVELIST list[1];
	moveGenarator.GenerateAllMoves(pos, bitboardProc, list, board);
	int moveNum = 0;
	for(moveNum=0; moveNum<list->count; ++moveNum)
	{
		if( !makeMove.MakeMoveOnBoard(pos, list->moves[moveNum].move, bitboardProc, board))
		{
			continue;
		}
		ExecPerft(depth - 1, pos, board, bitboardProc);
		makeMove.ReverseMoveOnBoard(pos, bitboardProc, board);
	}
}


