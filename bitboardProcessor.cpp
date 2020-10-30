#include "BitboardProcessor.h"
#include <cstdio>
void BitboardProcessor::PrintBitBoard(U64 bb)
{
	U64 shiftMe = 1ULL;

	printf("\n");

	/*
	 * Navigate from 8th rank to first rank, walk across files, i.e. from
	 * a8 to h8, then from a7 to h7 and so on, until you hit a1 to h1.
	 */
	for(int rank = RANK_8; rank >= RANK_1; --rank)
	{
		for(int file = FILE_A; file <= FILE_H; ++file)
		{
			int sq = FR2SQ(file, rank);		//Get the square index - 120 based.
			int sq64 = SQ64(sq);			//Convert it to 64 based index.

			//If a pawn exists on this square, we want to print X, otherwise -
			if ((shiftMe << sq64) & bb)
				printf("X");
			else printf("=");
		}
		printf("\n");
	}
}

int BitboardProcessor::CountBits(U64 b)
{
	int r;
	for (r = 0; b; r++, b &= b - 1);
	return r;
}

int BitboardProcessor::PopBit(U64* bb)
{
	U64 b = *bb ^ (*bb - 1);
	unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32));
	*bb &= (*bb - 1);
	return BitTable[(fold * 0x783a9b23) >> 26];
}



