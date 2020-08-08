#include "Move.h"
#pragma warning(disable: 4996)			//Disable windows compiler's moaning about sprintf function.

char* Move::PrintSquare(const int sq)
{
	static char SqStr[3];

	int file = FilesBrd[sq];
	int rank = RanksBrd[sq];

	sprintf(SqStr, "%c%c", ('a' + file), ('1' + rank));

	return SqStr;
}

char* Move::PrintMove(const int move)
{
	static char MvStr[6];

	int ff = FilesBrd[FROMSQ(move)];			//File from
	int rf = RanksBrd[FROMSQ(move)];			//Rank from
	int ft = FilesBrd[TOSQ(move)];				//File to
	int rt = RanksBrd[TOSQ(move)];				//Rank to

	int promoted = PROMOTED(move);				//If promotion then to what piece

	if(promoted)
	{
		char pchar = 'q';
		if(IsKn(promoted))
		{
			pchar = 'n';
		}else if(IsRQ(promoted) && !IsBQ(promoted))		//If its a rook or queen but not bishop or queen then it has to be rook
		{
			pchar = 'r';
		}else if(!IsRQ(promoted) && IsBQ(promoted))		//If its not a rook or quen but is bishop or queen then it has to be a bishop
		{
			pchar = 'b';
		}
		sprintf(MvStr, "%c%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt), pchar);
	}else
	{
		sprintf(MvStr, "%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt));
	}

	return MvStr;
}

void Move::PrintMoveList(const S_MOVELIST* movelist)
{
	int index = 0;
	int score = 0;
	int move = 0;
	printf("MoveList:\n", movelist->count);

	for(index=0; index<movelist->count; ++index)
	{
		move = movelist->moves[index].move;
		score = movelist->moves[index].score;

		printf("Move: %d > %s (score:%d)\n", index + 1, PrintMove(move), score);
	}
	printf("MoveList Total %d Moves:\n\n", movelist->count);
}

