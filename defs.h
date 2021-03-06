// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
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
#define BRD_SQ_NUM 120																//Board Square Number - bord with 2 borders on top and bottom and 1 border on left and right.

#define MAXGAMEMOVES 2048															//Maximum number of moves a game can be of.
#define MAXPOSITIONMOVES 256														//Maximum number of moves a position can have (candidate moves)

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"		//FEN representation of initial position of a chess board.
#define FEN2 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"			//FEN representation of position after 1.e4. Used for testing only.
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"		//FEN representation of position after 1.e4 c5. Used for testing only.
#define FEN4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"	//??
#define FENQUEENSATTACKINGEACHOTHER "8/3q4/8/8/4Q3/8/8/8 w - - 0 2 "												//This is an illegal position but helps us test attacks of queens on each other.
#define PAWNMOVESW "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"	//Test position 1
#define PAWNMOVESB "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b - e3 0 1"		//Test position 2
#define KNIGHTSKINGS "5k2/1n6/4n3/6N1/8/3N4/8/5K2 w - - 0 1"						//Test position 3
#define ROOKS "6k1/8/5r2/8/1nR5/5N2/8/6K1 w - - 0 1"								//Test position 4
#define QUEENS "6k1/8/4nq2/8/1nQ5/5N2/1N6/6K1 w - - 0 1 "							//Test position 5
#define BISHOPS "6k1/1b6/4n3/8/1n4B1/1B3N2/1N6/2b3K1 b - - 0 1 "					//Test position 6
#define CASTLE1 "r3k2r/8/8/8/8/8/8/R3K2R b KQkq - 0 1"								//Test position 7
#define CASTLE2 "3rk2r/8/8/8/8/8/6p1/R3K2R w KQK - 0 1"								//Test position 8
#define CASTLE3 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"	//Test position 9

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};						//Enum value indicates type of piece, e.g. Black King has value of 12.
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};	//Enum value indicates file index
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};	//Enum value indicates rank index

enum { WHITE, BLACK, BOTH};															//White = 0, Black = 1, Both = 2

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
};																					//Refer to Diagram 1 in Notes.txt.

enum { FALSE, TRUE};																//FALSE = 0, TRUE = 1

//Castling permissions - these will be represented in single byte with 4 bits.
enum {WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};		

typedef struct{
	int move;							//This points to actual move, see GAME MOVE note below
	int score;							//Will be used for move ordering
}S_MOVE;


typedef struct
{
	S_MOVE moves[MAXPOSITIONMOVES];
	int count;
}S_MOVELIST;

////////////////////////////MOVE GENERATION//////////////////////////////
//[V24 and V25]
/*
 *	0000	0000	0000	0000	0000	0111	1111	-> From				0x7F
 *	0000	0000	0000	0000	1111	1000	0000	-> To				>>7, 0x3F
 *	0000	0000	0011	1100	0000	0000	0000	-> Captured			>>14, 0xF
 *	0000	0000	0100	0000	0000	0000	0000	-> EP				0x40000
 *	0000	0000	1000	0000	0000	0000	0000	-> Pawn Start		0x80000
 *	0000	1111	0000	0000	0000	0000	0000	-> Promoted Piece	>>20, 0xF
 *	0001	0000	0000	0000	0000	0000	0000	-> Castle			0x1000000
 */

//Refer to the Notes.txt, Move Generation section.
#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m)>>7) & 0x7F)
#define CAPTURED(m) (((m)>>14) & 0xF)
#define PROMOTED(m) (((m) >> 20) & 0xF)

#define MFLAGEP 0x40000
#define MFLAGPS 0x80000
#define MFLAGCA 0x1000000

#define MFLAGCAP 0x7c000
#define MFLAGPROM 0xF00000

////////////////////////////MOVE GENERATION//////////////////////////////

typedef struct
{
	int move;					//Move that needs to be undone
	int castlePerm;				//Castling permissions before the move
	int enPas;					//En-passant square (if there was one active)
	int fiftyMove;				//Status of the fifty move rule at this point
	U64 posKey;					//Position key of the position to which we want to go to
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

	int ply;										//Indicates half moves in current search
	int histPly;									//Total half moves in the past. Required to trace threefold repetition.

	int castlePerm;									//Indicates castling permissions

	U64 posKey;										//Unique key generated for each position. Useful to track repetitions in position.
	int pceNum[13];									//Number of pieces on board, indexed by piece type (wP, wN, wB, wR, wQ, wK, bP, wN, wB, wR, wQ)

	int bigPce[2];									//All pieces except pawns
	int majPce[2];									//Rooks and Queens (white, black)
	int minPce[2];									//Bishops and Knights (white, black)
	int material[2];								//'Material' score (white, black)

	//Before making a move the current position info will be stored here
	S_UNDO history[MAXGAMEMOVES];					//The history of moves can be used to track 3-fold repetition using position keys

	//This array contains number of instances of each type of piece on board.
	int pList[13][10];								//For each piece type (wP/bP/wR/bR etc.) there can be 10 instances present on the board (promotion included.)
	
} S_BOARD;


/*Macros*/
#define FR2SQ(f,r) ( (21 + (f)) + ((r)*10))			//When given a file and rank, this returns 120 board based index number.
#define SQ64(sq120) Sq120ToSq64[sq120]				//Shortcut to Sq120ToSq64 defined in globals below, defined for convenience.
#define SQ120(sq64) Sq64ToSq120[sq64]				//Shortcut to Sq64ToSq120  defined in globals below, defined for convenience.
#define CLRBIT(bb, sq) ((bb) &= ClearMask[(sq)])	//Takes a bitboard, performs bitwise AND operation.
#define SETBIT(bb, sq) ((bb) |= SetMask[(sq)])		//Takes a bitboard, performs exclusive OR operation.
//#define POP(b) PopBit(b)
//#define CNT(b) CountBits(b)
/*Functions*/

/*Globals*/
extern int Sq120ToSq64[BRD_SQ_NUM];					//Converts 120 index board position to 64 index boar position.
extern int Sq64ToSq120[64];							//Converts 64 index board position to 120 index board position.
extern U64 SetMask[64];								//
extern U64 ClearMask[64];							//

extern U64 PieceKeys[13][120];						//Dimension[0] is for piece, dimension[1] is for the square
extern U64 sideKey;									//
extern U64 castleKeys[16];							//Four bits to represent 4 castling ways (2 ways for each side).

//Arrays below are used for printing board position
//on screen next to the bitboard layout.
extern char PceChar[];								//.PNBRQKpnbrqk - Pieces on board
extern char SideChar[];								//wb- Side to move
extern char RankChar[];								//123456789 - Rank index
extern char FileChar[];								//abcdefgh- File index

//Arrays below are used to track various properties belonging to a piece.
//We need 14 elements because we are tracking 6 original pieces + 8 potential
//new pieces which can be obtained by pawn promotions.
//Note that we can not promote the pawn to a King.
extern int PieceBig[13];							//Indicates if piece is 'big' (queen)
extern int PieceMaj[13];							//Indicates if piece is 'major' (Rook)
extern int PieceMin[13];							//Indicates if piece is minor (knight/bishop)
extern int PieceVal[13];							//Indicates relevant piece value
extern int PieceCol[13];							//Indicates color of a given piece
extern int PiecePawn[13];							//Indicates if a given piece is a pawn

extern int FilesBrd[BRD_SQ_NUM];
extern int RanksBrd[BRD_SQ_NUM];

//These arrays indicate what kind of piece it is, that is attacking on a given square X
extern int PieceKnight[13];							//Is the attacking piece a knight
extern int PieceKing[13];							//Is the attacking piece a King
extern int PieceRookQueen[13];						//Is the attacking piece a Queen
extern int PieceBishopQueen[13];					//Is the attacking piece a Bishop or Queen (diagonal attack)
extern int PieceSlides[13];							//Is the attacking piece a sliding piece (Rook or Queen)

#define IsBQ(p) (PieceBishopQueen[(p)])
#define IsRQ(p) (PieceRookQueen[(p)])
#define IsKn(p) (PieceKnight[(p)])
#define IsKi(p) (PieceKing[(p)])

#endif
