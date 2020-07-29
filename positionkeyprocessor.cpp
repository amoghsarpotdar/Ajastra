#include <stdio.h>
#include "positionkeyprocessor.h"


///This function calculates the position key based on current position of pieces,
///side to move, and castling position. These factors are important because
///any minor diference in these three factors will result into unique position key.
/////TODO : Unit tests required for this logic.
U64 positionkeyprocessor::GeneratePosKey(const S_BOARD* pos)
{
	int sq = 0;
	U64 finalKey = 0;
	int piece = EMPTY;

	//Iterate through the board squares, ignore the off-board squares
	//If the square has a piece on it, use it to calculate the position key. 
	for(sq=0; sq<BRD_SQ_NUM; ++sq)
	{
		piece = pos->pieces[sq];
		if(piece!=NO_SQ && piece != EMPTY && piece != OFFBOARD)
		{
			ASSERT(piece >= wP && piece <= bK);
			finalKey ^= PieceKeys[piece][sq];
		}
	}

	if(pos->side == WHITE)
	{
		finalKey ^= sideKey;
	}

	if(pos->enPass != NO_SQ)
	{
		ASSERT(pos->enPass >= 0 && pos->enPass < BRD_SQ_NUM);
		finalKey ^= PieceKeys[EMPTY][pos->enPass];
	}

	ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);
	finalKey ^= castleKeys[pos->castlePerm];

	return finalKey;
}

