#pragma once
#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdlib.h>

#define DEBUG

//TODO : Translate the following C macro into C++ style.
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if (!(n)){	\
		printf("%s - Failed ", #n); \
		printf("On %s ", __DATE__); \
		printf("At %s ", __TIME__); \
		printf("In File %s ", __FILE__); \
		printf("At Line %d\n", __LINE__); \
		exit(1);}
#endif

typedef unsigned long long U64;

#define NAME "Ajastra 1.0"
#define BRD_SQ_NUM 120

#define MAXGAMEMOVES 2048

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"		//FEN representation of initial position of a chess board.
#define FEN2 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"			//FEN representation of position after 1.e4. Used for testing only.
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"		//FEN representation of position after 1.e4 c5. Used for testing only.

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};

enum { WHITE, BLACK, BOTH};

enum
{
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

enum { FALSE, TRUE};

enum {WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};			//Castling permissions

typedef struct
{
	int move;
	int castlePerm;
	int enPas;
	int fiftyMove;
	U64 posKey;
}S_UNDO;

typedef struct
{
	int pieces[BRD_SQ_NUM];
	U64 pawns[3];				//00000000 - 8 0s indicating 8 squares on row. Note that this is unsigned 64 bit value.
								//Where there is a pawn, bit is set to 1, if not 0.
								//Represent WHITE, BLACK and BOTH.
								//Pawns are already represented in pieces[] above but
								//when finding ranks, evaluating position etc. looking
								//at pawns on their own will be much easier and faster.
								
	int KingSq[2];				//Squares on which Kings are
	int side;					//Side to move
	int enPass;					//En-passant square (active)
	int fiftyMovesTracker;		//Counter to trace fifty moves rule

	int ply;					//Indicates half moves in current search
	int histPly;				//Total half moves in the past. Required to trace threefold repetition.

	int castlePerm;				//Indicates castling permissions

	U64 posKey;					//Unique key generated for each position. Useful to track repetitions in position.
	int pceNum[13];				//Number of pieces on board, indexed by piece type (wP, wN, wB, wR, wQ, wK, bP, wN, wB, wR, wQ)

	int bigPce[2];				//All pieces except pawns
	int majPce[2];				//Rooks and Queens (white, black)
	int minPce[2];				//Bishops and Knights (white, black)
	int material[2];			//'Material' score (white, black)

	S_UNDO history[MAXGAMEMOVES];

	int pList[13][10];			//For each piece type (wP/bP/wR/bR etc.) there can be 10 instances present on the board (promotion included.
	
} S_BOARD;;

/*Macros*/
#define FR2SQ(f,r) ( (21 + (f)) + ((r)*10))			//When given a file and rank, this returns 120 board based index number.
#define SQ64(sq120) Sq120ToSq64[sq120]				//Shortcut to Sq120ToSq64 defined in globals below, defined for convenience.
#define SQ120(sq64) Sq64ToSq120[sq64]				//Shortcut to Sq64ToSq120  defined in globals below, defined for convenience.
#define CLRBIT(bb, sq) ((bb) &= ClearMask[(sq)])	//Takes a bitboard, performs bitwise AND operation.
#define SETBIT(bb, sq) ((bb) |= SetMask[(sq)])		//Takes a bitboard, performs exclusive OR operation.

/*Functions*/

/*Globals*/
extern int Sq120ToSq64[BRD_SQ_NUM];					//Converts 120 index board position to 64 index boar position.
extern int Sq64ToSq120[64];							//Converts 64 index board position to 120 index board position.
extern U64 SetMask[64];								//
extern U64 ClearMask[64];							//

extern U64 PieceKeys[13][120];						//Dimension[0] is for piece, dimension[1] is for the square
extern U64 sideKey;									//
extern U64 castleKeys[16];							//Four bits to represent 4 castling ways (2 ways for each side).

extern char PceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

extern int PieceBig[13];
extern int PieceMaj[13];
extern int PieceMin[13];
extern int PieceVal[13];
extern int PieceCol[13];

#endif
