#pragma once
#ifndef _MOVEGENERATOR_H_
#define _MOVEGENERATOR_H_
#include "Attack.h"

class MoveGenerator
{
public:
	void AddQuietMove(const S_BOARD* position, int move, S_MOVELIST *movelist);
	void AddCaptureMove(const S_BOARD* position, int move, S_MOVELIST *movelist);
	void AddEnPassantMove(const S_BOARD* position, int move, S_MOVELIST* movelist);
	void GenerateAllMoves(const S_BOARD* position, S_MOVELIST* movelist);
};

#endif
