#include "Attack.h"


#include "Board.h"
#include "Validator.h"

//Possible incoming attack directions on to a square.
const int KnDir[8] = { -8, -19, -21, -12, 8, 19, 21, 12 };		//Knight's attack squares onto a square X
const int RkDir[4] = { -1, -10, 1, 10 };						//Rook's attack squares onto a square X
const int BiDir[4] = { -9, -11, 11, 9 };						//Bishop's attack squares onto a square X
const int KiDir[8] = { -1, -10, 1, 10, -9, -11, 11, 9 };		//King's attack squares onto a square X

//These arrays indicate what kind of piece it is, that is attacking on a given square X
//int PieceKnight[13] = { FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE };
//int PieceKing[13] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE };
//int PieceRookQueen[13] = { FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE };
//int PieceBishopQueen[13] = { FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE };

int PiecePawn[13] = { FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE };
int PieceKnight[13] = { FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE };
int PieceKing[13] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE };
int PieceRookQueen[13] = { FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE };
int PieceBishopQueen[13] = { FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE };


int Attack::SqAttacked(const int sq, const int side, const S_BOARD* pos, bitboardProcessor bitboardproc, Board board)
{
	int pce, index, t_sq, dir;

	Validator validator;
	//Board board;

	ASSERT(validator.SqOnBoard(sq));			//Ensure that square is on board.
	ASSERT(validator.SideValid(side));			//Ensure that correct side is set to move.
	ASSERT(board.CheckBoard(pos, bitboardproc));

	//Check attacks by pawns
	if(side == WHITE)
	{
		if(pos->pieces[sq-11] == wP || pos->pieces[sq-9] == wP)
		{
			return TRUE;
		}
	}else
	{
		if (pos->pieces[sq+11] == bP || pos->pieces[sq+9] == bP)
			return TRUE;
	}

	//Check attacks by knights
	for(index=0;index<8;++index)
	{
		pce = pos->pieces[sq + KnDir[index]];				//Get the piece on KnDir[index] position from piece array

		if (pce != EMPTY && pce != OFFBOARD) {
			if (IsKn(pce) && PieceCol[pce] == side)				//If the piece is a knight and of color we are looking for
			{
				return TRUE;									//This square is being attacked by the knight
			}
		}
	}

	//Check attacks by rooks and queens (straight line attacks)
	for(index=0; index<4; ++index)
	{
		dir = RkDir[index];
		t_sq = sq + dir;
		pce = pos->pieces[t_sq];
		while(pce != OFFBOARD)
		{
			if(pce!=EMPTY)
			{
				if(IsRQ(pce) && PieceCol[pce] == side)
				{
					return TRUE;
				}
				break;
			}
			t_sq += dir;
			pce = pos->pieces[t_sq];
		}
	}

	//Check attacks by bishops and queens (diagonal attacks)
	for(index=0; index<4; ++index)
	{
		dir = BiDir[index];
		t_sq = sq + dir;
		pce = pos->pieces[t_sq];
		while(pce != OFFBOARD)
		{
			if(pce != EMPTY)
			{
				if(IsBQ(pce) && PieceCol[pce] == side)
				{
					return TRUE;
				}
				break;
			}
			t_sq += dir;
			pce = pos->pieces[t_sq];
		}
	}

	//Check attacks by kings (king attacks)
	for(index=0; index<8; ++index)
	{
		pce = pos->pieces[sq + KiDir[index]];
		if(IsKi(pce) && PieceCol[pce] == side)
		{
			return TRUE;
		}
	}

	return FALSE;
}

