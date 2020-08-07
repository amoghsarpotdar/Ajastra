#pragma once
#ifndef _MOVE_H_
#define _MOVE_H_

#include <stdio.h>
#include "Attack.h"

class Move
{
public:
	char* PrintSquare(const int sq);
	char* PrintMove(const int move);
};

#endif


