#include "Init.h"

#include <cstdio>

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

void init::AllInit()
{
	InitSq120To64();
	InitBitMasks();
	InitHashKeys();
	InitFilesRanksBrd();
}

void init::InitFilesRanksBrd()
{
	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;
	int sq64 = 0;

	for(index=0; index<BRD_SQ_NUM; ++index)
	{
		FilesBrd[index] = OFFBOARD;
		RanksBrd[index] = OFFBOARD;
	}

	for(rank=RANK_1; rank<= RANK_8; ++rank)
	{
		for(file=FILE_A; file<=FILE_H; ++file)
		{
			sq = FR2SQ(file, rank);
			FilesBrd[sq] = file;
			RanksBrd[sq] = rank;
		}
	}

	printf("FilesBrd\n");
	for(index=0; index<BRD_SQ_NUM; ++index)
	{
		if (index % 10 == 0 && index != 0) printf("\n");
		printf("%4d", FilesBrd[index]);
	}

	printf("\n");
	printf("RanksBrd\n");
	for(index=0; index<BRD_SQ_NUM; ++index)
	{
		if (index % 10 == 0 && index != 0) printf("\n");
		printf("%4d", RanksBrd[index]);
	}
}


void init::InitHashKeys()
{
	int index = 0;
	int index2 = 0;
	for(index=0;index<13;++index)
	{
		for(index2=0;index2<120;++index2)
		{
			PieceKeys[index][index2] = RAND_64;
		}
	}
	sideKey = RAND_64;
	for(index=0;index<16;++index)
	{
		castleKeys[index] = RAND_64;
	}
}


void init::InitBitMasks()
{
	int index = 0;

	//This initializes the bitmask arrays to default 0ULL value.
	for(index=0; index<64; index++)
	{
		SetMask[index] = 0ULL;
		ClearMask[index] = 0ULL;
	}

	//This initializes the SetMask and ClearMask arrays respectively.
	for(index=0; index<64; index++)
	{
		//Uses the bitwise left shift to set 'index' square to 1
		SetMask[index] |= (1ULL << index);
		//Uses the bitwise NOT operation to set 'index' square to its opposite value (0 if it is 1 and otherwise)
		ClearMask[index] = ~SetMask[index];
	}
}


void init::InitSq120To64()
{
	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;
	int sq64 = 0;

	for (index = 0; index < BRD_SQ_NUM; ++index)
	{
		Sq120ToSq64[index] = 65;
	}

	for (index = 0; index < 64; ++index)
	{
		Sq64ToSq120[index] = 120;
	}

	for (rank = RANK_1; rank <= RANK_8; ++rank)
	{
		for (file = FILE_A; file <= FILE_H; ++file)
		{
			sq = FR2SQ(file, rank);
			Sq64ToSq120[sq64] = sq;
			Sq120ToSq64[sq] = sq64;
			sq64++;
		}
	}
}


