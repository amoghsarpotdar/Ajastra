// Ajastra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "defs.h"
#include "Init.h"
#include "bitboard.h"

int main(){

	
	return 0;
}

/**************************TESTS***********************************/
void TestClearMaskForGivenSquare()
{
	init _initializer;
	bitboard board;
	_initializer.AllInit();
	bitboard bitboard;

	int index = 0;
	U64 playBitBoad = 0ULL;

	for (index = 0; index < 64; index++)
	{
		printf("Index: %d", index);
		board.PrintBitBoard(ClearMask[index]);
		printf("\n");
	}
}

void TestSetMaskSetsBitForGivenSquare()
{
	init _initializer;
	bitboard board;
	_initializer.AllInit();
	bitboard bitboard;

	int index = 0;
	U64 playBitBoad = 0ULL;

	for (index = 0; index < 64; index++)
	{
		printf("Index: %d", index);
		board.PrintBitBoard(SetMask[index]);
		printf("\n");
	}
	SETBIT(playBitBoad, 61);
	board.PrintBitBoard(SetMask[index]);
}

void TestPopBitboardFunctionV2()
{
	init _initializer;
	bitboard board;
	_initializer.AllInit();

	U64 playBitBoard = 0ULL;

	playBitBoard |= (1ULL << SQ64(D2));
	playBitBoard |= (1ULL << SQ64(D3));
	playBitBoard |= (1ULL << SQ64(D4));

	int sq64 = 0;

	while (playBitBoard)
	{
		sq64 = board.PopBit(&playBitBoard);
		printf("Popped: %d\n", sq64);
		board.PrintBitBoard(playBitBoard);
	}
}

void TestPopBitBoardFunction()
{
	init _initializer;
	_initializer.AllInit();

	U64 playBitBoard = 0ULL;

	playBitBoard |= (1ULL << SQ64(D2));
	playBitBoard |= (1ULL << SQ64(D3));
	playBitBoard |= (1ULL << SQ64(D4));

	printf("\n");
	bitboard board;
	board.PrintBitBoard(playBitBoard);

	int count = board.CountBits(playBitBoard);
	printf("Count: %d\n", count);

	int index = board.PopBit(&playBitBoard);
	printf("index:%d\n", index);
	board.PrintBitBoard(playBitBoard);
	count = board.CountBits(playBitBoard);
	printf("Count: %d\n", count);
}

void TestPawnBitBoard()
{
	init _initializer;
	_initializer.AllInit();

	U64 playBitBoard = 0ULL;

	printf("start:\n\n");
	bitboard board;
	board.PrintBitBoard(playBitBoard);

	//Add a pawn to D2.
	playBitBoard |= (1ULL << SQ64(D2));
	printf("D2 Added:\n\n");
	board.PrintBitBoard(playBitBoard);

	//Add a pawn to G2.
	playBitBoard |= (1ULL << SQ64(G2));
	printf("G2 Added:\n\n");
	board.PrintBitBoard(playBitBoard);
}

void TestBoardPrintingMechanism()
{
	init _initializer;
	_initializer.AllInit();
	int index = 0;

	//Testing ASSERT macro in defs.h. Remember to #define DEBUG.
	//TODO : Move this into a unit test.
	//int num = 4;
	//ASSERT(index == num);

	//Testing the board printing mechanism.
	//TODO : Move this into a unit test.
	for (index = 0; index < BRD_SQ_NUM; ++index)
	{
		if (index % 10 == 0)
			std::cout << "\n";

		printf("%5d", Sq120ToSq64[index]);
	}

	printf("\n");
	printf("\n");

	for (index = 0; index < 64; ++index)
	{
		if (index % 8 == 0)
			printf("\n");

		printf("%5d", Sq64ToSq120[index]);
	}
}

void TestAssertMacro()
{
	int index = 0;

	//Testing ASSERT macro in defs.h. Remember to #define DEBUG.
	//TODO : Move this into a unit test.
	int num = 4;
	ASSERT(index == num);
}
/**************************TESTS***********************************/


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
