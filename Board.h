#pragma once
#ifndef _BOARD_H_
#define _BOARD_H_

#include "defs.h"


class Board
{
public:
	void ResetBoard(S_BOARD* pos);
	void PrintBoard(const S_BOARD* pos);
	int Parse_Fen(const char* fen, S_BOARD* pos);
	void UpdateListsMaterial(S_BOARD* pos);
};

#endif
