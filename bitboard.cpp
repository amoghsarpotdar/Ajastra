#include "bitboard.h"

void bitboard::PrintBitBoard(U64 bb)
{
	U64 shiftMe = 1ULL;

	int rank = 0;
	int file = 0;
	int sq = 0;
	int sq64 = 0;

	printf("\n");

	/*
	 * Navigate from 8th rank to first rank, walk across files, i.e. from
	 * a8 to h8, then from a7 to h7 and so on, until you hit a1 to h1.
	 */
	for(rank = RANK_8; rank >= RANK_1; --rank)
	{
		for(file = FILE_A; file <= FILE_H; ++file)
		{
			sq = FR2SQ(file, rank);		//Get the square index - 120 based.
			sq64 = SQ64(sq);			//Convert it to 64 based index.

			//If a pawn exists on this square, we want to print X, otherwise -
			if ((shiftMe << sq64) & bb)
				printf("X");
			else printf("=");
		}
		printf("\n");
	}
}

int bitboard::CountBits(U64 b)
{
	int r;
	for (r = 0; b; r++, b &= b - 1);
	return r;
}

int bitboard::PopBit(U64* bb)
{
	U64 b = *bb ^ (*bb - 1);
	unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32));
	*bb &= (*bb - 1);
	return BitTable[(fold * 0x783a9b23) >> 26];
}



