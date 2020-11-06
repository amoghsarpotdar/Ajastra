#pragma once
#ifndef _BITBOARDPROCESSOR_H_
#define _BITBOARDPROCESSOR_H_

#include "defs.h"

/// <summary>
/// This class provides framework to track pawns on a board using bitboard
/// container. Note that we are using bitboards only to deal with pawns, not
/// pieces. The pieces are being stored in array p_List defined in defs.h.
/// </summary>
class BitboardProcessor
{

private:
	/**/
	const int BitTable[64] = {
		63,30,3,32,25,41,22,33,15,50,42,13,11,53,19,34,61,29,2,
		51,21,43,45,10,18,47,1,54,9,57,0,35,62,31,40,4,49,5,52,
		26,60,6,23,44,46,27,56,16,7,39,48,24,59,14,12,55,38,28,
		58,20,37,17,36,8
	};
	
public:
	void PrintBitBoard(U64 bb);
	

	//////////////////////////////
	//More information available on chess programming wiki about the functions defined in this block.
	int PopBit(U64* bb);			//Takes least significant bit, returns index this bit was set at and sets the bit to 0.
	int CountBits(U64 b);			//Counts and returns number of '1's in a bitboard.
	//////////////////////////////


};

#endif
