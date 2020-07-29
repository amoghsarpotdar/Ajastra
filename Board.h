#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include "stdio.h"
#include "defs.h"
#include "defs.h"

class Board
{
public:
	void ResetBoard(S_BOARD* pos);
	int Parse_Fen(char* fen, S_BOARD* pos);
};

#endif

