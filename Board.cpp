#include "Board.h"

void Board::ResetBoard(S_BOARD* pos)
{
	int index = 0;

	for(index=0; index<BRD_SQ_NUM; ++index)
	{
		pos->pieces[index] = OFFBOARD;
	}

	for(index=0; index<64; ++index)
	{
		pos->pieces[SQ120(index)] = EMPTY;
	}

	for(index=0;index<3;++index)
	{
		pos->bigPce[index] = 0;
		pos->majPce[index] = 0;
		pos->minPce[index] = 0;
		pos->pawns[index] = 0ULL;
	}

	for(index=0; index<13; ++index)
	{
		pos->pceNum[index] = 0;
	}

	pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

	pos->side = BOTH;
	pos->enPass = NO_SQ;
	pos->fiftyMovesTracker = 0;
	pos->ply = 0;
	pos->castlePerm = 0;
	pos->posKey = 0ULL;
}

