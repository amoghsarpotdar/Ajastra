#pragma once
#ifndef _MAKE_MOVE_H_
#define _MAKE_MOVE_H_

#include "defs.h"
#include "Board.h"

class BitboardProcessor;

class MakeMove
{

public:
	void ClearPiece(const int sq, S_BOARD *pos);
	void AddPiece(const int sq, S_BOARD* pos, const int pce);
	void MovePiece(int from, int to, S_BOARD* pos);
	int MakeMoveOnBoard(S_BOARD *pos, int move, BitboardProcessor bitboardprocessor, Board board);
	int ReverseMoveOnBoard(S_BOARD* pos, BitboardProcessor bitboardprocessor, Board board);;
	
private:
    const int CastlePerm[120] = {
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 13, 15, 15, 15, 12, 15, 15, 14, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15,  7, 15, 15, 15,  3, 15, 15, 11, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15
    };
};
#endif



