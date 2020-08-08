#include "Validator.h"

#include "defs.h"

int Validator::FileRankValid(const int fr)
{
	return (fr >= 0 && fr <= 7) ? 1 : 0;
}

int Validator::PieceValid(const int pce)
{
	return (pce >= EMPTY && pce <= bK) ? 1 : 0;
}

int Validator::PieceValidEmpty(const int pce)
{
	return (pce >= EMPTY && pce <= bK) ? 1 : 0;
}

int Validator::SideValid(const int side)
{
	return (side == WHITE || side == BLACK) ? 1 : 0;
}

int Validator::SqOnBoard(const int sq)
{
	return FilesBrd[sq] == OFFBOARD ? 0 : 1;
}





