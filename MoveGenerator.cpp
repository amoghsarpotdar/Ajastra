#include "MoveGenerator.h"

void MoveGenerator::AddQuietMove(const S_BOARD* position, int move, S_MOVELIST* movelist)
{
	movelist->moves[movelist->count].move = move;
	movelist->moves[movelist->count].score = 0;
	movelist->count++;
}

void MoveGenerator::AddCaptureMove(const S_BOARD* position, int move, S_MOVELIST* movelist)
{
	movelist->moves[movelist->count].move = move;
	movelist->moves[movelist->count].score = 0;
	movelist->count++;
}

void MoveGenerator::AddEnPassantMove(const S_BOARD* position, int move, S_MOVELIST* movelist)
{
	movelist->moves[movelist->count].move = move;
	movelist->moves[movelist->count].score = 0;
	movelist->count++;
}

void MoveGenerator::GenerateAllMoves(const S_BOARD* position, S_MOVELIST* movelist)
{
	movelist->count = 0;
}


