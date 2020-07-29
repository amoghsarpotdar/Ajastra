#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include "stdio.h"
#include "defs.h"
#include "positionkeyprocessor.h"

U64 PieceKeys[13][120];						//Dimension[0] is for piece, dimension[1] is for the square
U64 sideKey;								//
U64 castleKeys[16];							//Four bits to represent 4 castling ways (2 ways for each side).

class Board
{
public:
	void ResetBoard(S_BOARD* pos);
	int Parse_Fen(char* fen, S_BOARD* pos);
};

#endif

