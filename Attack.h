#pragma once
#ifndef _ATTACK_H_
#define _ATTACK_H_

#include "defs.h"

class bitboardProcessor;

class Attack
{
	public:
		int SqAttacked(const int sq, const int side, const S_BOARD* pos, bitboardProcessor bitboardproc);
};

#endif

