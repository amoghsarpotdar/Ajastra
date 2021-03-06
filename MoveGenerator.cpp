#include "stdio.h"
#include "MoveGenerator.h"
#include "Board.h"
#include "Move.h"
#include "Validator.h"

//This builds a move by shifting relevant bits.
#define MOVE(f,t,ca,pro,fl) ((f) | ((t) << 7) | ((ca) << 14) | ((pro) << 20) | (fl))

//This checks if a square is off board or not.
#define SQOFFBOARD(sq) (FilesBrd[(sq)] == OFFBOARD)

/// <summary>
/// This function adds a quiet move to move list.
/// </summary>
/// <param name="position">Constant pointer to S_BOARD structure variable</param>
/// <param name="move">Integer specifying move details</param>
/// <param name="movelist">Pointer to list of moves</param>
void MoveGenerator::AddQuietMove(const S_BOARD* position, int move, S_MOVELIST* movelist)
{
	movelist->moves[movelist->count].move = move;
	movelist->moves[movelist->count].score = 0;
	movelist->count++;
}

/// <summary>
/// This function adds a capture move to move list.
/// </summary>
/// <param name="position">Constant pointer to S_BOARD structure variable</param>
/// <param name="move">Integer specifying move details</param>
/// <param name="movelist">Pointer to list of moves</param>
void MoveGenerator::AddCaptureMove(const S_BOARD* position, int move, S_MOVELIST* movelist)
{
	movelist->moves[movelist->count].move = move;
	movelist->moves[movelist->count].score = 0;
	movelist->count++;
}

/// <summary>
/// This function adds En-passant move to move list.
/// </summary>
/// <param name="position">Constant pointer to S_BOARD structure variable</param>
/// <param name="move">Integer specifying move details</param>
/// <param name="movelist">Pointer to list of moves</param>
void MoveGenerator::AddEnPassantMove(const S_BOARD* position, int move, S_MOVELIST* movelist)
{
	movelist->moves[movelist->count].move = move;
	movelist->moves[movelist->count].score = 0;
	movelist->count++;
}

/// <summary>
/// Adds possible White Pawn moves to the move list.
/// If Pawn is moving from 7th square to 8th, it will be promoted to either a Queen,
/// Rook, Bishop or a Knight.
/// </summary>
/// <param name="pos">Constant pointer to S_BOARD structure variable</param>
/// <param name="from">Square from which to move</param>
/// <param name="to">Square to which to move</param>
/// <param name="cap"></param>
/// <param name="movelist">Pointer to list of moves</param>
void MoveGenerator::AddWhitePawnCaptureMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* movelist)
{
	Validator validator;
	
	ASSERT(validator.PieceValidEmpty(cap));
	ASSERT(validator.SqOnBoard(from));
	ASSERT(validator.SqOnBoard(to));
	
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

/// <summary>
/// Adds possible capture moves for Black pawn to moves list.
/// If Pawn is moving from 7th square to 8th, it will be promoted to either a Queen,
/// Rook, Bishop or a Knight.
/// </summary>
/// <param name="pos">Constant pointer to S_BOARD structure</param>
/// <param name="from">Square from which to move</param>
/// <param name="to">Square to which to move</param>
/// <param name="cap"></param>
/// <param name="movelist">Pointer to S_MOVELIST structure</param>
void MoveGenerator::AddBlackPawnCaptureMove(const S_BOARD* pos, const int from, const int to, const int cap, S_MOVELIST* movelist)
{
	Validator validator;

	ASSERT(validator.PieceValidEmpty(cap));
	ASSERT(validator.SqOnBoard(from));
	ASSERT(validator.SqOnBoard(to));
	
	if (RanksBrd[from] == RANK_2)
	{
		AddCaptureMove(pos, MOVE(from, to, cap, bQ, 0), movelist);
		AddCaptureMove(pos, MOVE(from, to, cap, bR, 0), movelist);
		AddCaptureMove(pos, MOVE(from, to, cap, bB, 0), movelist);
		AddCaptureMove(pos, MOVE(from, to, cap, bN, 0), movelist);
	}
	else
	{
		AddCaptureMove(pos, MOVE(from, to, cap, EMPTY, 0), movelist);
	}
}

/// <summary>
/// Adds a possible White pawn move to pawn moves list.
/// </summary>
/// <param name="pos">Constant pointer to S_BOARD structure</param>
/// <param name="from">Square from which to move</param>
/// <param name="to">Square to which to move</param>
/// <param name="movelist">Pointer to S_MOVELIST structure</param>
void MoveGenerator::AddWhitePawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* movelist)
{
	Validator validator;

	ASSERT(validator.SqOnBoard(from));
	ASSERT(validator.SqOnBoard(to));
	
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

/// <summary>
/// Adds a possible Black pawn move to pawn moves list.
/// </summary>
/// <param name="pos">Constant pointer to S_BOARD structure</param>
/// <param name="from">Square from which to move</param>
/// <param name="to">Square to which to move</param>
/// <param name="movelist">Pointer to S_MOVELIST structure</param>
void MoveGenerator::AddBlackPawnMove(const S_BOARD* pos, const int from, const int to, S_MOVELIST* movelist)
{
	Validator validator;

	ASSERT(validator.SqOnBoard(from));
	ASSERT(validator.SqOnBoard(to));
	
	if (RanksBrd[from] == RANK_2)
	{
		AddQuietMove(pos, MOVE(from, to, EMPTY, bQ, 0), movelist);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bR, 0), movelist);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bB, 0), movelist);
		AddQuietMove(pos, MOVE(from, to, EMPTY, bN, 0), movelist);
	}
	else
	{
		AddQuietMove(pos, MOVE(from, to, EMPTY, EMPTY, 0), movelist);
	}
}



/// <summary>
/// TODO : This function needs refactoring into smaller parts
/// 
/// </summary>
/// <param name="pos"></param>
/// <param name="bitboardproc"></param>
/// <param name="movelist"></param>
/// <param name="board"></param>
void MoveGenerator::GenerateAllMoves(const S_BOARD* pos,BitboardProcessor bitboardproc, S_MOVELIST *movelist, Board board)
{
	Validator validator;
	Attack attack;
	
	ASSERT(board.CheckBoard(pos, bitboardproc));

	movelist->count = 0;

	int pce = EMPTY;
	int side = pos->side;
	int sq = 0; int t_sq = 0;
	int pceNum = 0;
	int dir = 0;
	int index = 0;
	int pceIndex = 0;
	Move mv;

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

		//Castling implementation for White
		//King side castling
		if (pos->castlePerm & WKCA)
		{
			if (pos->pieces[F1] == EMPTY && pos->pieces[G1] == EMPTY)
			{
				if (!attack.SqAttacked(E1, BLACK, pos, bitboardproc, board) && !attack.SqAttacked(F1, BLACK, pos, bitboardproc, board))
				{
					AddQuietMove(pos, MOVE(E1, G1, EMPTY, EMPTY, MFLAGCA), movelist);
				}
			}
		}

		//Queenside castling
		if (pos->castlePerm & WQCA)
		{
			if (pos->pieces[D1] == EMPTY && pos->pieces[C1] == EMPTY && pos->pieces[B1] == EMPTY)
			{
				if (!attack.SqAttacked(E1, BLACK, pos, bitboardproc, board) && !attack.SqAttacked(D1, BLACK, pos, bitboardproc, board))
				{
					AddQuietMove(pos, MOVE(E1, C1, EMPTY, EMPTY, MFLAGCA), movelist);
				}
			}
		}
	}
	else
	{
		for(pceNum = 0; pceNum < pos->pceNum[bP]; ++pceNum)
		{
			sq = pos->pList[bP][pceNum];
			ASSERT(validator.SqOnBoard(sq));

			if(pos->pieces[sq - 10] == EMPTY)
			{
				AddBlackPawnMove(pos, sq, sq - 10, movelist);
				if(RanksBrd[sq] == RANK_7 && pos->pieces[sq-20] == EMPTY)
				{
					AddQuietMove(pos, MOVE(sq, (sq - 20), EMPTY, EMPTY, MFLAGPS), movelist);
				}
			}

			if(!SQOFFBOARD(sq - 9) && PieceCol[pos->pieces[sq - 9]] == WHITE)
			{
				AddBlackPawnCaptureMove(pos, sq, sq - 9, pos->pieces[sq - 9], movelist);
			}

			if(!SQOFFBOARD(sq - 11) && PieceCol[pos->pieces[sq - 11]] == WHITE)
			{
				AddBlackPawnCaptureMove(pos, sq, sq - 11, pos->pieces[sq - 11], movelist);
			}

			if(sq - 9 == pos->enPass)
			{
				AddCaptureMove(pos, MOVE(sq, sq - 9, EMPTY, EMPTY, MFLAGEP), movelist);
			}
			if(sq - 11 == pos->enPass)
			{
				AddCaptureMove(pos, MOVE(sq, sq - 11, EMPTY, EMPTY, MFLAGEP), movelist);
			}
		}

		//Castling implementation for black
		//King side castling
		if (pos->castlePerm & BKCA)
		{
			if (pos->pieces[F8] == EMPTY && pos->pieces[G8] == EMPTY)
			{
				if (!attack.SqAttacked(E8, WHITE, pos, bitboardproc, board) && !attack.SqAttacked(F8, WHITE, pos, bitboardproc, board))
				{
					AddQuietMove(pos, MOVE(E1, G1, EMPTY, EMPTY, MFLAGCA), movelist);
				}
			}
		}

		//Queenside castling
		if (pos->castlePerm & BQCA)
		{
			if (pos->pieces[D8] == EMPTY && pos->pieces[C8] == EMPTY && pos->pieces[B8] == EMPTY)
			{
				if (!attack.SqAttacked(E8, WHITE, pos, bitboardproc, board) && !attack.SqAttacked(D8, WHITE, pos, bitboardproc, board))
				{
					AddQuietMove(pos, MOVE(E8, C8, EMPTY, EMPTY, MFLAGCA), movelist);
				}
			}
		}
	}

	/*Move generation for sliding pieces*/
	pceIndex = LoopSlideIndex[side];
	pce = LoopSlidePce[pceIndex++];
	
	while(pce != 0)
	{
		ASSERT(validator.PieceValid(pce));

		for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
		{
			sq = pos->pList[pce][pceNum];
			ASSERT(validator.SqOnBoard(sq));
			printf("Piece:%c on %s\n", PceChar[pce], mv.PrintSquare(sq));
			//For each direction applicable to this piece
			for (index = 0; index < NumDir[pce]; ++index)
			{
				dir = PceDir[pce][index];
				t_sq = sq + dir;
				//With sliding pieces, its not only one square in a given direction but
				//all squares till we reach the 'off-board' square.
				while (!SQOFFBOARD(t_sq)) {
					//If the target square is not empty...
					if (pos->pieces[t_sq] != EMPTY)
					{
						//...and if the color of the piece on target square is not same as the color of our piece
						if (PieceCol[pos->pieces[t_sq]] == (side^1))						//0 (black) EXOR 1 is 1 (white), and 1 (white) EXOR 1 is 0 (black)
						{
							AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), movelist);
						}
						//We have to break out of the loop because we have encountered a piece
						//in our path.
						break;			
					}
					AddQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), movelist);
					t_sq += dir;
				}
			}
		}
		pce = LoopSlidePce[pceIndex++];
	}

	/*Move generation for non-sliding pieces*/
	pceIndex = LoopNonSlideIndex[side];
	pce = LoopNonSlidePce[pceIndex++];
	while( pce != 0)
	{
		ASSERT(validator.PieceValid(pce));
		printf("non slider pceindex: %d pce:%d\n", pceIndex, pce);

		for(pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
		{
			sq = pos->pList[pce][pceNum];
			ASSERT(validator.SqOnBoard(sq));
			printf("Piece:%c on %s\n", PceChar[pce], mv.PrintSquare(sq));
			//For each direction applicable to this piece
			for(index=0; index<NumDir[pce]; ++index)
			{
				dir = PceDir[pce][index];
				t_sq = sq + dir;
				//Skip this square if it is off the board.
				if(SQOFFBOARD(t_sq))
				{
					continue;
				}
				//If the target square is not empty...
				if(pos->pieces[t_sq] != EMPTY)
				{
					//...and if the color of the piece on target square is not same as the color of our piece
					if(PieceCol[pos->pieces[t_sq]] == (side ^ 1))						//0 (black) EXOR 1 is 1 (white), and 1 (white) EXOR 1 is 0 (black)
					{
						AddCaptureMove(pos, MOVE(sq, t_sq, pos->pieces[t_sq], EMPTY, 0), movelist);
					}
					continue;
				}else
				{
					AddQuietMove(pos, MOVE(sq, t_sq, EMPTY, EMPTY, 0), movelist);
				}
			}
		}

		pce = LoopNonSlidePce[pceIndex++];
	}
}


