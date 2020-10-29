#pragma once
#ifndef _ATTACK_H_
#define _ATTACK_H_

#include "defs.h"
#include "BitboardProcessor.h"
#include "Board.h"

class Attack
{
	public:
		int SqAttacked(const int sq, const int side, const S_BOARD* pos, BitboardProcessor bitboardproc, Board board);
};

#endif

