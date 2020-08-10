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
	const int LoopSlidePce[8] = {
		wB, wR, wQ, 0, bB, bR, bQ, 0
	};
	const int LoopSlideIndex[2] = { 0, 4 };

	//Index to track non-sliding piece navigation
	const int LoopNonSlidePce[6] = {
		wN, wK, 0, bN, bK, 0
	};
	const int LoopNonSlideIndex[2] = { 0, 3 };

	//Directional movements for pieces
	//This indicates the directions in which each piece can move in, not applicable for pawns
	const int PceDir[13][8] = {
		{0,0,0,0,0,0,0},							//Empty
		{0,0,0,0,0,0,0},							//wP (not applicable)
		{-8,-19,-21,-12,8,19,21,12},				//wN
		{-9,-11,11,9,0,0,0,0},						//wB
		{-1,-10,1,10,0,0,0,0},						//wR
		{-1,-10,1,10,-9,-11,11,9},					//wQ
		{-1,-10,1,10,-9,-11,11,9},					//wK?
		{0,0,0,0,0,0,0},							//bP (not applicable)
		{-8,-19,-21,-12,8,19,21,12},				//bN
		{-9,-11,11,9,0,0,0,0},						//bB
		{-1,-10,1,10,0,0,0,0},						//bR
		{-1,-10,1,10,-9,-11,11,9},					//bQ
		{-1,-10,1,10,-9,-11,11,9}					//bK?
	};

	//This array indicates number of directions applicable to each piece type, not applicable for pawns
	//EMPTY,wP(not applicable),wN,wB,wR,wQ,wK,bP(not applicable),bN,bB,bR,bQ,bK
	int NumDir[13] = {
		0,0,8,4,4,8,8,0,8,4,4,8,8
	};
};

#endif
