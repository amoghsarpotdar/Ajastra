#pragma once
#include "defs.h"
#include "bitboard.h"

U64 PieceKeys[13][120];						//Dimension[0] is for piece, dimension[1] is for the square
U64 sideKey;								//
U64 castleKeys[16];							//Four bits to represent 4 castling ways (2 ways for each side).

class positionkeyprocessor
{
public:
	U64 GeneratePosKey(const S_BOARD* pos);
};

