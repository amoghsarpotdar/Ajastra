#include "Init.h"

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

void Init::AllInit()
{
	InitSq120To64();
	InitBitMasks();
	InitHashKeys();
	InitFilesRanksBrd();
}

void Init::InitFilesRanksBrd()
{
	for(int index = 0; index<BRD_SQ_NUM; ++index)
	{
		FilesBrd[index] = OFFBOARD;
		RanksBrd[index] = OFFBOARD;
	}

	//Go through all files and ranks, for each square here
	for(int rank = RANK_1; rank<= RANK_8; ++rank)
	{
		for(int file = FILE_A; file<=FILE_H; ++file)
		{
			int sq = FR2SQ(file, rank);
			FilesBrd[sq] = file;
			RanksBrd[sq] = rank;
		}
	}

	/*printf("FilesBrd\n");
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
	}*/
}


void Init::InitHashKeys()
{
	int index;
	int index2;
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


void Init::InitBitMasks()
{
	int index;

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


void Init::InitSq120To64()
{
	int index;
	int file;
	int rank;
	int sq;
	int sq64 = 0;

	//Initializing 64-square array.
	//Initialize default value - 65 - this is the invalid value
	//i.e. should never be returned as a valid square value.
	//Valid value for a square should range from 0 to 63.
	for (index = 0; index < BRD_SQ_NUM; ++index)
	{
		Sq120ToSq64[index] = 65;
	}

	//Initializing 120-square array.
	//The default value indicating off-board square is 120, so
	//initializing all elements to 120 (OFF_BOARD square).
	for (index = 0; index < 64; ++index)
	{
		Sq64ToSq120[index] = 120;
	}

	//This loop initializes the 'valid' squares on board.
	//It iterates through ranks and files, picking every
	//individual square on a file vs. rank it initializes
	//relevant square using Sq64ToSq120 for 120 bit array and
	//Sq120To64 for 64 squares array. Squares initialized in here
	//are the only valid squares. Remaining squares shall continue
	//returning their default values initialized in the two loops above.
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


