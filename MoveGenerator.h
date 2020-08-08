#pragma once
#ifndef _MOVEGENERATOR_H_
#define _MOVEGENERATOR_H_
#include "Attack.h"
#include "bitboardProcessor.h"
#include "Board.h"


class MoveGenerator
{
public:
	void AddQuietMove(const S_BOARD* position, int move, S_MOVELIST *movelist);
	void AddCaptureMove(const S_BOARD* position, int move, S_MOVELIST *movelist);
	void AddWhitePawnCaptureMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* movelist);
	void AddWhitePawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* movelist);
	void AddEnPassantMove(const S_BOARD* position, int move, S_MOVELIST *movelist);
	void AddBlackPawnCaptureMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* movelist);
	void AddBlackPawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* movelist);
	
	void GenerateAllMoves(const S_BOARD* pos, bitboardProcessor bitboardproc, S_MOVELIST *movelist, Board board);
};

#endif
