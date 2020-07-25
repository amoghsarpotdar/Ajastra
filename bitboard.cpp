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

