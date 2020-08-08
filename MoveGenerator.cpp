#include "stdio.h"
#include "MoveGenerator.h"
#include "Board.h"
#include "Validator.h"

//This builds a move by shifting relevant bits.
#define MOVE(f,t,ca,pro,fl) ((f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl))

//This checks if a square is off board or not.
#define SQOFFBOARD(sq) (FilesBrd[(sq)] == OFFBOARD)

void MoveGenerator::AddQuietMove(const S_BOARD* position, int move, S_MOVELIST* movelist)
{
	movelist->moves[movelist->count].move = move;
	movelist->moves[movelist->count].score = 0;
	movelist->count++;
}

void MoveGenerator::AddCaptureMove(const S_BOARD* position, int move, S_MOVELIST* movelist)
{
	movelist->moves[movelist->count].move = move;
	movelist->moves[movelist->count].score = 0;
	movelist->count++;
}

void MoveGenerator::AddWhitePawnCaptureMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* movelist)
{
	if(RanksBrd[from] == RANK_7)
	{
		AddCaptureMove(pos, MOVE(from, to, cap, wQ, 0), movelist);
		AddCaptureMove(pos, MOVE(from, to, cap, wR, 0), movelist);
		AddCaptureMove(pos, MOVE(from, to, cap, wB, 0), movelist);
		AddCaptureMove(pos, MOVE(from, to, cap, wN, 0), movelist);
	}else
	{
		AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), movelist);
	}
}

void MoveGenerator::AddWhitePawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* movelist)
{
	if(RanksBrd[from] == RANK_7)
	{
		AddQuietMove(pos, MOVE(from, to, EMPTY, wQ, 0), movelist);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wR, 0), movelist);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wB, 0), movelist);
		AddQuietMove(pos, MOVE(from, to, EMPTY, wN, 0), movelist);
	}else
	{
		AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), movelist);
	}
}


void MoveGenerator::AddEnPassantMove(const S_BOARD* position, int move, S_MOVELIST* movelist)
{
	movelist->moves[movelist->count].move = move;
	movelist->moves[movelist->count].score = 0;
	movelist->count++;
}

void MoveGenerator::GenerateAllMoves(const S_BOARD* pos,bitboardProcessor bitboardproc, S_MOVELIST *movelist, Board board)
{
	Validator validator;
	
	ASSERT(board.CheckBoard(pos, bitboardproc));

	movelist->count = 0;

	int pce = EMPTY;
	int side = pos->side;
	int sq = 0; int t_sq = 0;
	int pceNum = 0;

	if(side == WHITE)
	{
		//Navigate through all White pawns.
		for(pceNum = 0; pceNum < pos->pceNum[wP]; ++pceNum)
		{
			sq = pos->pList[wP][pceNum];						//Get the position of this pawn on board.
			ASSERT(validator.SqOnBoard(sq));					//Ensure that the pawn is on a valid board square.

			//When pawn is on its initial square, it can move one or two squares, if those squares are empty.
			if(pos->pieces[sq + 10] == EMPTY)														//If first square in path is empty
			{
				AddWhitePawnMove(pos, sq, sq + 10, movelist);									//Then use this as a potential move
				if(RanksBrd[sq] == RANK_2 && pos->pieces[sq+20] == EMPTY)							//If the second square is empty
				{
					AddQuietMove(pos, MOVE(sq, (sq + 20), EMPTY, EMPTY, MFLAGPS), movelist);	//Then use this as a potential move
				}
			}

			//Check if there exists a black pawn or piece on square ahead diagonally.
			//The square will be +9 or +11 on our 120 based board.
			if(!SQOFFBOARD(sq + 9) && PieceCol[pos->pieces[sq + 9]] == BLACK)
			{
				AddWhitePawnCaptureMove(pos, sq, sq + 9, pos->pieces[sq + 9], movelist);
			}
			if(!SQOFFBOARD(sq + 11) && PieceCol[pos->pieces[sq+11]] == BLACK)
			{
				AddWhitePawnCaptureMove(pos, sq, sq + 11, pos->pieces[sq + 11], movelist);
			}

			//Check if we have enPassant capture possibility
			//TODO : Determine if we need a check to ensure sq+9 and sq+11 are not OFFBOARD squares.
			if(sq + 9 == pos->enPass)
			{
				AddCaptureMove(pos, MOVE(sq, sq + 9, EMPTY, EMPTY, MFLAGEP), movelist);
			}
			if(sq + 11 == pos->enPass)
			{
				AddCaptureMove(pos, MOVE(sq, sq + 11, EMPTY, EMPTY, MFLAGEP), movelist);
			}
		}
	}else
	{
		
	}
}


