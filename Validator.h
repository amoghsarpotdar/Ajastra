#pragma once
#ifndef _VALIDATOR_H_
#define _VALIDATOR_H_

#include <stdio.h>

class Validator
{
public:
	int SqOnBoard(const int sq);
	int SideValid(const int side);
	int FileRankValid(const int fr);
	int PieceValidEmpty(const int pce);
	int PieceValid(const int pce);
};

#endif
