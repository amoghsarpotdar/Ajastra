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

private:
	//When generating moves, depending upon side to move we loop through the array below
	//and generate moves for each piece, until we hit the 0.

	//Index to track sliding piece navigation
	int LoopSlidePce[8] = {
		wB, wR, wQ, 0, bB, bR, bQ, 0
	};
	int LoopSlideIndex[2] = { 0, 4 };

	//Index to track non-sliding piece navigation
	int LoopNonSlidePce[6] = {
		wN, wK, 0, bN, bK, 0
	};
	int LoopNonSlideIndex[2] = { 0, 3 };

	//Directional movements for pieces
	//This indicates the directions in which each piece can move in, not applicable for pawns
	int PceDir[13][8] = {
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0},							//Not applicable for pawns
		{-8,-19,-21,-12,8,19,21,12},				//White knight - can move in 8 directions
		{-9,-11,11,9,0,0,0,0},						//White bishop - can move in 4 directions
		{-1,-10,1,10,0,0,0,0},						//White rook - can move in 4 directions
		{-1,-10,1,10,-9,-11,11,9},
		{-1,-10,1,10,-9,-11,11,9},
		{0,0,0,0,0,0,0},							//Not applicable for pawns
		{-8,-19,-21,-12,8,19,21,12},				//Black knight - can move in 8 directions
		{-9,-11,11,9,0,0,0,0},						//Black bishop - can move in 4 directions
		{-1,-10,1,10,0,0,0,0},						//Black rook - can move in 4 directions
		{-1,-10,1,10,-9,-11,11,9},
		{-1,-10,1,10,-9,-11,11,9}
	};

	//This array indicates number of directions applicable to each piece type, not applicable for pawns
	int NumDir[13] = {
		0,0,8,4,4,8,8,0,8,4,4,8,8
	};
};

#endif
