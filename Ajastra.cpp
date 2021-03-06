// Ajastra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>


#include "BitboardProcessor.h"
#include "Board.h"
#include "Init.h"
#include "Attack.h"
#include "MakeMove.h"
#include "Move.h"
#include "MoveGenerator.h"
#include "Perft.h"


int main(){

	Init _initializer;
	Board theboard;
	BitboardProcessor bitboardProcessor;
	S_BOARD board[1] = {};
	/*Move mv;
	MakeMove mkv;
	MoveGenerator movegenerator;*/
	Perft perfTest;
	

	_initializer.AllInit();
	theboard.ParseFen(START_FEN, board);
	theboard.PrintBoard(board);

	//S_MOVELIST movelist[1];
	theboard.ParseFen(START_FEN, board);
	perfTest.ResetState();
	perfTest.ExecPerfTest(4, board, theboard, bitboardProcessor);

}






/**************************TESTS***********************************/
/*
 *

void VerifyMoveGeneration()
{
	Init _initializer;
	Board theboard;
	BitboardProcessor bitboardProcessor;
	S_BOARD board[1] = {};
	Move mv;
	MakeMove mkv;
	MoveGenerator movegenerator;

	_initializer.AllInit();
	theboard.ParseFen(START_FEN, board);
	theboard.PrintBoard(board);

	S_MOVELIST movelist[1];
	movegenerator.GenerateAllMoves(board, bitboardProcessor, movelist, theboard);
	mv.PrintMoveList(movelist);

	int keyPressed = getchar();

	int move = 0;
	bool skip = false;
	for (int moveNum = 0; moveNum < movelist->count; ++moveNum)
	{
		move = movelist->moves[moveNum].move;
		if (!mkv.MakeMoveOnBoard(board, move, bitboardProcessor, theboard))
		{
			printf("mkv.MakeMoveOnBoard failed.");
			continue;
		}

		printf("\nMADE: %s\n", mv.PrintMove(move));
		theboard.PrintBoard(board);

		mkv.ReverseMoveOnBoard(board, bitboardProcessor, theboard);
		printf("\nTAKEN: %s\n", mv.PrintMove(move));
		theboard.PrintBoard(board);

		keyPressed = getchar();
	}
}

void TestCastlingMoveGeneration2()
{
	Init _initializer;
	Board theboard;
	BitboardProcessor BitboardProcessor;
	S_BOARD board[1] = {};
	Move mv;
	MoveGenerator movegenerator;

	_initializer.AllInit();
	theboard.ParseFen(CASTLE3, board);
	theboard.PrintBoard(board);

	S_MOVELIST movelist[1];
	movegenerator.GenerateAllMoves(board, BitboardProcessor, movelist, theboard);
	mv.PrintMoveList(movelist);

}

void TestCastlingMoveGeneration1()
{
	Init _initializer;
	Board theboard;
	BitboardProcessor BitboardProcessor;
	S_BOARD board[1] = {};
	Move mv;
	MoveGenerator movegenerator;

	_initializer.AllInit();
	theboard.ParseFen(CASTLE2, board);
	theboard.PrintBoard(board);

	S_MOVELIST movelist[1];
	movegenerator.GenerateAllMoves(board, BitboardProcessor, movelist, theboard);
	//mv.PrintMoveList(movelist);
}

void TestSldingPieceMoveGenerationWithBishops()
{
	Init _initializer;
	Board theboard;
	BitboardProcessor BitboardProcessor;
	S_BOARD board[1] = {};
	Move mv;
	MoveGenerator movegenerator;

	_initializer.AllInit();
	theboard.ParseFen(BISHOPS, board);
	theboard.PrintBoard(board);

	S_MOVELIST movelist[1];
	movegenerator.GenerateAllMoves(board, BitboardProcessor, movelist, theboard);
	//mv.PrintMoveList(movelist);
}

void TestNonSlidingPieceMoveGenerationWithKnights()
{
	Init _initializer;
	Board theboard;
	BitboardProcessor BitboardProcessor;
	S_BOARD board[1] = {};
	Move mv;
	MoveGenerator movegenerator;

	_initializer.AllInit();
	theboard.ParseFen(KNIGHTSKINGS, board);
	theboard.PrintBoard(board);

	S_MOVELIST movelist[1];
	movegenerator.GenerateAllMoves(board, BitboardProcessor, movelist, theboard);
	//mv.PrintMoveList(movelist);

}

void TestPawnMoveGeneration()
{
	Init _initializer;
	Board theboard;
	BitboardProcessor BitboardProcessor;
	S_BOARD board[1] = {};
	Move mv;
	MoveGenerator movegenerator;

	_initializer.AllInit();
	theboard.ParseFen(PAWNMOVESW, board);
	theboard.PrintBoard(board);

	S_MOVELIST movelist[1];
	movegenerator.GenerateAllMoves(board, BitboardProcessor, movelist, theboard);
	//mv.PrintMoveList(movelist);
}

 void TestGenerateAllMoves1()
{
	Init _initializer;
	Board theboard;
	BitboardProcessor BitboardProcessor;
	S_BOARD board[1] = {};
	Move mv;
	MoveGenerator movegenerator;

	_initializer.AllInit();
	theboard.ParseFen(PAWNMOVESB, board);
	theboard.PrintBoard(board);

	S_MOVELIST movelist[1];
	movegenerator.GenerateAllMoves(board, BitboardProcessor, movelist, theboard);
	mv.PrintMoveList(movelist);
}

[V26]
void TestPrintBinary()
{
	Init _initializer;
	Board theboard;
	bitboard bitBoard;
	S_BOARD board[1] = {};
	Move mv;

	_initializer.AllInit();
	theboard.PrintBoard(board);

	int move = 0;
	int from = A2;
	int to = H7;
	int cap = wR;
	int prom = bK;

	move = ((from) | (to << 7) | (cap << 14) | (prom << 20));

	printf("from:%d to:%d cap:%d prom:%d\n", FROMSQ(move), TOSQ(move), CAPTURED(move), PROMOTED(move));

	printf("Algebraic from:%s\n", mv.PrintSquare(from));
	printf("Algebraic to:%s\n", mv.PrintSquare(to));
	printf("Algebraic move:%s\n", mv.PrintMove(move));
}

[V26]
void PrintBinary(int move)
{
	int index = 0;
	printf("As binary: \n");
	for (index = 27; index >= 0; index--)
	{
		if ((1 << index) & move) printf("1");
		else printf("0");
		if (index != 28 && index % 4 == 0) printf(" ");
	}
	printf("\n");
}

[V26]
void TestMovePrint()
{
	Init _initializer;
	Board theboard;
	bitboard bitBoard;
	S_BOARD board[1] = {};

	_initializer.AllInit();
	//theboard.ParseFen(FENQUEENSATTACKINGEACHOTHER, board);
	theboard.PrintBoard(board);

	int move = 0, from = 6, to = 12;
	int cap = wR; int prom = bR;
	move = ((from) | (to << 7) | (cap << 14) | (prom << 20));
	printf("\ndec: %d hex: %X\n", move, move);
	PrintBinary(move);
	printf("from:%d to:%d cap:%d prom:%d\n", FROMSQ(move), TOSQ(move), CAPTURED(move), PROMOTED(move));
	//move |= MFLAGPS;
	printf("is PST : %s \n", (move & MFLAGPS) ? "YES" : "NO");
	return 0;
}

void TestSqAttackedBySide()
{
	Init _initializer;
	Board theboard;
	bitboard bitBoard;
	S_BOARD board[1] = {};

	_initializer.AllInit();
	theboard.ParseFen(FENQUEENSATTACKINGEACHOTHER, board);
	theboard.PrintBoard(board);

	printf("\n\nWhite Attacking:\n");
	ShowSqAttackedBySide(WHITE, board);

	printf("\n\nBlack Attacking:\n");
	ShowSqAttackedBySide(BLACK, board);
}

//TODO : Generate more test cases based on various types of pieces.
//Convert these functions to unit tests.
//Possible test cases are -
//1. Squares attacked by King, Queen, Knight, Bishop, Rook, Pawn
//2. Squares attacked by pieces with their own pawn in path
//3. Squares attacked by pieces with opposite color pawn in path
void ShowSqAttackedBySide(const int side, const S_BOARD* pos)
{
	int rank = 0;
	int file = 0;
	int sq = 0;
	Attack attack;

	printf("\n\nSquares attacked by :%c\n", SideChar[side]);
	for (rank = RANK_8; rank >= RANK_1; --rank)
	{
		for (file = FILE_A; file <= FILE_H; ++file)
		{
			sq = FR2SQ(file, rank);
			if ((attack.SqAttacked(sq, side, pos)) == TRUE)
			{
				printf("X");
			}
			else
			{
				printf("-");
			}
		}
		printf("\n");
	}
	printf("\n");
}


void TestCheckBoardAsserts()
{
	Init _initializer;
	Board theboard;
	bitboard bitBoard;
	S_BOARD board[1] = {};

	_initializer.AllInit();
	theboard.ParseFen(FEN4, board);
	theboard.PrintBoard(board);
	printf("\nForced asserts...\n");
	board->pceNum[wP]--;
	ASSERT(theboard.CheckBoard(board, bitBoard));
}

void TestInitFilesRanksBrd()
{
	Init _initializer;
	Board _board;
	_initializer.AllInit();
}

void TestClearMaskForGivenSquare()
{
	Init _initializer;
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
	Init _initializer;
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
	Init _initializer;
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
	Init _initializer;
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
	Init _initializer;
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
	Init _initializer;
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
*/
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
