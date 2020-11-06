#include "MakeMove.h"



#include "Attack.h"
#include "Board.h"
#include "Validator.h"

//Hashing macros
#define HASH_PCE(pce,sq) (pos->posKey ^= (PieceKeys[(pce)][(sq)]))			//Hashing piece
#define HASH_CA (pos->posKey ^= (castleKeys[(pos->castlePerm)]))			//Hashing castling permissions
#define HASH_SIDE (pos->posKey ^= (sideKey))								//Hashing side to move
#define HASH_EP (pos->posKey ^= (PieceKeys[EMPTY][(pos->enPass)]))			//Hashing en-passant square


/// <summary>
/// This function removes a given piece/pawn from our in-memory representation of bitboard.
/// It also removes relevant piece/pawn from the piece type arrays.
/// </summary>
/// <param name="sq"></param>
/// <param name="pos"></param>
void MakeMove::ClearPiece(const int sq, S_BOARD* pos)
{
	Validator validator;
	ASSERT(validator.SqOnBoard(sq));							//Ensure that square is on the board

	int pce = pos->pieces[sq];									//Get the piece on this square
	ASSERT(validator.PieceValid(pce));							//Ensure that this is a valid piece

	int col = PieceCol[pce];									//Get the color of piece
	int index = 0;
	int t_pceNum = -1;

	HASH_PCE(pce, sq);										//X-OR the piece from position key to update our key

	pos->pieces[sq] = EMPTY;									//Set the target square to empty
	pos->material[col] -= PieceVal[pce];						//Update our material score to reflect removal of piece

	//If this is a 'big' piece, it must be either a major piece or a minor one
	if(PieceBig[pce])
	{
		pos->bigPce[col]--;
		if(PieceMaj[pce]){
			pos->majPce[col]--;									//If major piece array has this, update it to reflect the change
		}else{
			pos->minPce[col]--;									//If minor piece array has this, update it to reflect the change
		}
	}else
	{
		CLRBIT(pos->pawns[col], SQ64(sq));						//Update the color-specific pawn array to reflect removal of pawn
		CLRBIT(pos->pawns[BOTH], SQ64(sq));						//Update the array containing both pawns to reflect removal of pawn
	}

	//Now we update the piece list that reflects number of pieces on board of a given type
	//Look for the index of the square, that matches square supplied in argument 'sq'
	for(index = 0; index < pos->pceNum[pce]; ++index)
	{
		if(pos->pList[pce][index] == sq)
		{
			t_pceNum = index;
			break;
		}
	}

	ASSERT(t_pceNum != -1);

	pos->pceNum[pce]--;													//Since we are removing a piece, update the value to reflect change in count
	pos->pList[pce][t_pceNum] = pos->pList[pce][pos->pceNum[pce]];		//Refer to [V39] if this becomes confusing
}

/// <summary>
/// Adds piece/pawn to specific square on a given board.
/// </summary>
/// <param name="sq">Integer pointing to target square on 120 index board.</param>
/// <param name="pos">Pointer to S_BOARD structure that contains our in-memory representation of board</param>
/// <param name="pce">Integer representing piece being added</param>
void MakeMove::AddPiece(const int sq, S_BOARD  *pos, const int pce)
{
	Validator validator;

	ASSERT(validator.PieceValid(pce));
	ASSERT(validator.SqOnBoard(sq));

	int col = PieceCol[pce];
	HASH_PCE(pce, sq);
	pos->pieces[sq] = pce;

	//Are we adding a 'big' piece?
	if(PieceBig[pce])
	{
		pos->bigPce[col]++;												//If so, update relevant array
		if(PieceMaj[pce])
		{
			pos->majPce[col]++;											//If its a major piece, update relevant array
		}else
		{
			pos->minPce[col]++;											//If its a minor piece, update relevant array
		}
	}else
	{
		SETBIT(pos->pawns[col], SQ64(sq));								//If we are adding a pawn then we need to update our pawns array of specific color
		SETBIT(pos->pawns[BOTH], SQ64(sq));								//and the array containing both pawns
	}
	pos->material[col] += PieceVal[pce];								//Update the material value of particular side to reflect change in material
	pos->pList[pce][pos->pceNum[pce]++] = sq;							//Update the 'count' of pieces on board for this piece type, notice the post increment operator.
	
}

/// <summary>
/// Moves the piece from source to target square.
/// Updates the piece/pawn position on bitboard.
/// </summary>
/// <param name="from">Square from which the piece is to be moved</param>
/// <param name="to">Square to which the piece is to be moved</param>
/// <param name="pos">Pointer to S_BOARD structure, which is our in-memory bitboard representation.</param>
void MakeMove::MovePiece(const int from, const int to, S_BOARD* pos)
{
	//Make sure that both squares are 'on board'
	Validator validator;
	ASSERT(validator.SqOnBoard(from));									
	ASSERT(validator.SqOnBoard(to));

	int index = 0;
	int pce = pos->pieces[from];
	int col = PieceCol[pce];

#ifdef DEBUG
	int t_PieceNum = FALSE;
#endif

	HASH_PCE(pce, from);
	pos->pieces[from] = EMPTY;											//Since this piece is moving, set the 'from' square to empty

	HASH_PCE(pce, to);
	pos->pieces[to] = pce;												//Set this piece in our 'to' square

	//If what we are dealing with is not a 'big' piece, then it must be a pawn
	if(!PieceBig[pce])
	{
		CLRBIT(pos->pawns[col], SQ64(from));							//Remove the bit flag from coloured pawn array
		CLRBIT(pos->pawns[BOTH], SQ64(from));							//Remove the bit flag from 'both' pawns array
		SETBIT(pos->pawns[col], SQ64(to));								//Set the bit flag for colored pawn array
		SETBIT(pos->pawns[BOTH], SQ64(to));								//Set the bit flag for 'both' pawns array
	}

	//Finally, we walk through our array containing all pieces and move it from its present square
	//(which must be 'from' square specified in parameter above) to the 'to' square (again supplied
	//as a parameter to the function).
	for(index=0; index<pos->pceNum[pce]; ++index)
	{
		if(pos->pList[pce][index] == from)
		{
			pos->pList[pce][index] = to;
#ifdef DEBUG
			t_PieceNum = TRUE;											//If this assert fails, that means our pList array is not aligned with actual piece positions
#endif
			break;
		}
	}
	ASSERT(t_PieceNum);
}

/// <summary>
/// Makes a move on S_BOARD structure instance - board representation in memory.
/// TODO : We need to break this into smaller functions.
/// TODO : Add unit tests for this function.
/// </summary>
/// <param name="pos">Pointer to S_BOARD structure</param>
/// <param name="move">Integer representing move to be made</param>
/// <param name="bitboardprocessor">Bitboard processor instance which will be used to perform bitboard processing operations</param>
/// <param name="board">Board object instance, used for performing validations on our board state</param>
/// <returns></returns>
int MakeMove::MakeMoveOnBoard(S_BOARD* pos, int move, BitboardProcessor bitboardprocessor, Board board)
{
	Validator validator;

	ASSERT(board.CheckBoard(pos, bitboardprocessor));									//Before we begin, ensure that board state is consistent.
	int from = FROMSQ(move);
	int to = TOSQ(move);
	int side = pos->side;

	ASSERT(validator.SqOnBoard(from));
	ASSERT(validator.SqOnBoard(to));
	ASSERT(validator.SideValid(side));
	ASSERT(validator.PieceValid(pos->pieces[from]));

	pos->history[pos->histPly].posKey = pos->posKey;									//Set current positionkey in history

	
	if(move & MFLAGEP)												//If the last move enabled en-passant possibility, then
	{
		if(side == WHITE)											//If it is Black capturing the pawn then we are capturing on White's								
		{															//3'rd rank with En-Passant. Remove the pawn on fourth row.
			ClearPiece(to - 10, pos);								//We obtain relevant square by deducing 10 squares.
			//Q : How can the fixed '-10' formula deal with en-passant on either side? i.e. if we reduce
			//10 form square index, for en-passant on left square, how do we deal with en-passant on the right wing?
		}else
		{
			ClearPiece(to + 10, pos);								//If it is White capturing the pawn, then number of squares
			//go in opposite direction.
		}
	}
	else if(move & MFLAGCA)																//If the last move sets up castling possibility, then
	{
		switch(to)
		{
		case C1:													//If the target square is C1
			MovePiece(A1, D1, pos);							//then move the Rook from A1 to D1
			break;
		case C8:													//If the target square is C8
			MovePiece(A8, D8, pos);							//then move the Rook from A8 to D8
			break;
		case G1:													//If the target square is G1
			MovePiece(H1, F1, pos);							//then move the Rook from H1 to F1
			break;													
		case G8:													//If the target square is G8
			MovePiece(H8, F8, pos);							//then move the piece from H8 to F8
			break;
		default: ASSERT(FALSE); break;								//If this assert fails, it indicates we have wrong 'to' square marked for castling
		}
	}

	if (pos->enPass != NO_SQ) HASH_EP;								//If we have a current en-passant square then hash it out
	HASH_CA;														//Hash out castling permissions

	pos->history[pos->histPly].move = move;
	pos->history[pos->histPly].fiftyMove = pos->fiftyMovesTracker;
	pos->history[pos->histPly].enPas = pos->enPass;
	pos->history[pos->histPly].castlePerm = pos->castlePerm;

	//If the Rook or King has moved from its original location then we need to update
	//castling permissions.
	pos->castlePerm &= CastlePerm[from];
	pos->castlePerm &= CastlePerm[to];
	pos->enPass = NO_SQ;

	HASH_CA;														//Hash in the new castling permissions state.

	//If a piece was captured, we need to reset the 50 moves rule tracker
	int captured = CAPTURED(move);														//Get the piece captured, if any
	pos->fiftyMovesTracker++;															//Increment the fifty move tracker

	if(captured != EMPTY)
	{
		ASSERT(validator.PieceValid(captured));
		ClearPiece(to, pos);
		pos->fiftyMovesTracker = 0;														//Reset the 50 moves tracker since a piece has been captured
	}

	//Increament the half move counter and move counter.
	pos->histPly++;
	pos->ply++;

	//We need to check if we need a new en-passent square set
	if(PiecePawn[pos->pieces[from]])													//If the piece moving is a pawn
	{
		pos->fiftyMovesTracker = 0;														//Reset the fifty move tracker according to chess rule
		if(move & MFLAGPS)																//Check if this move was a pawn start move
		{
			if(side == WHITE)															//If last move was White's move
			{
				pos->enPass = from + 10;
				ASSERT(RanksBrd[pos->enPass] == RANK_3);								//Ensure that en-passent square is on rank 3
			}else																		//Else if it was Black's move
			{
				pos->enPass = from - 10;
				ASSERT(RanksBrd[pos->enPass] == RANK_6);								//Ensure that en-passent square is on rank 6
			}
			HASH_EP;
		}
	}

	MovePiece(from, to, pos);

	//Check if promotion is applicable
	int prPce = PROMOTED(move);
	if(prPce != EMPTY)
	{
		ASSERT(validator.PieceValid(prPce) && !PiecePawn[prPce]);
		ClearPiece(to, pos);															//Remove the pawn that is being moved
		AddPiece(to, pos, prPce);														//Add the piece that pawn promotes to
	}

	if(PieceKing[pos->pieces[to]])														//If the move involved king, then update the king's square
	{
		pos->KingSq[pos->side] = to;
	}

	pos->side ^= 1;																		//Change the 'side to move' indicator
	HASH_SIDE;	
	
	ASSERT(board.CheckBoard(pos, bitboardprocessor));									//After all these changes, we need to ensure the board state is consistent.

	//Check if the square in which king currently stands is under attack.
	//If so, this is an illegal move and we need to revert it.
	Attack attack;
	if(attack.SqAttacked(pos->KingSq[side], pos->side, pos, bitboardprocessor, board))
	{
		ReverseMoveOnBoard(pos, bitboardprocessor,board);																
		return FALSE;
	}
	return TRUE;
}

/// <summary>
/// Reverses the move that was made on board.
/// </summary>
/// <param name="pos"></param>
/// <param name="bitboardprocessor"></param>
/// <param name="board"></param>
/// <returns></returns>
int MakeMove::ReverseMoveOnBoard(S_BOARD* pos, BitboardProcessor bitboardprocessor, Board board)
{
	Validator validator;

	ASSERT(board.CheckBoard(pos,bitboardprocessor));									//Before we begin, ensure the board is in consistent state

	//Decrement the history variables
	pos->histPly--;																		
	pos->ply--;

	int move = pos->history[pos->histPly].move;											//Get the last move
	int from = FROMSQ(move);															//Get the 'from' square for this move
	int to = TOSQ(move);																//Get the 'to' square for this move

	ASSERT(validator.SqOnBoard(from));
	ASSERT(validator.SqOnBoard(to));

	if (pos->enPass != NO_SQ) HASH_EP;													//If the enpassent square was not empty then hash it
	HASH_CA;																			//Hash the castle permission

	pos->castlePerm = pos->history[pos->histPly].castlePerm;							//Restore the castling permissions to previous state
	pos->fiftyMovesTracker = pos->history[pos->histPly].fiftyMove;						//Restore the fifty move state
	pos->enPass = pos->history[pos->histPly].enPas;										//Restore the en-pass flag

	if (pos->enPass != NO_SQ) HASH_EP;													//If en-passent square is note empty then hash it

	//Process the castling state
	HASH_CA;																			

	pos->side ^= 1;
	HASH_SIDE;

	
	if(MFLAGEP & move)																	//If this was an en-pass capture
	{
		if(pos->side == WHITE)
		{
			AddPiece(to - 10, pos, bP);											//If White made the en-pass capture, we add the White pawn back in
		}else
		{
			AddPiece(to + 10, pos, wP);											//If Black made the en-pass capture, we add the Black pawn back in
		}
	}else if(MFLAGCA & move)
	{
		switch(to)
		{
		case C1: MovePiece(D1, A1, pos); break;									//If the target square was c1, this must be long castling, so move the rook back to a1
		case C8: MovePiece(D8, A8, pos); break;									//If the target square was c8, this must be long castling, so move the rook back to a8
		case G1: MovePiece(F1, H1, pos); break;									//If the target square was f1, this must be long castling, so move the rook back to h1
		case G8: MovePiece(F8, H8, pos); break;									//If the target square was c1, this must be long castling, so move the rook back to h8
		default: ASSERT(FALSE); break;
		}
	}

	//Now that we are moving in reverse direction, switch the position of to and from
	MovePiece(to, from, pos);

	//Update the King's position
	if(PieceKing[pos->pieces[from]])
	{
		pos->KingSq[pos->side] = from;
	}

	int captured = CAPTURED(move);
	if(captured != EMPTY)
	{
		ASSERT(validator.PieceValid(captured));
		AddPiece(to, pos, captured);
	}

	//If the last move was promotion, then we need to roll it back as well.
	if(PROMOTED(move) != EMPTY)
	{
		ASSERT(validator.PieceValid(PROMOTED(move)) && !PiecePawn[PROMOTED(move)]);
		ClearPiece(from, pos);
		AddPiece(from, pos, (PieceCol[PROMOTED(move)] == WHITE ? wP : bP));
	}
	ASSERT(board.CheckBoard(pos, bitboardprocessor));									//Finally, make sure that we leave the board in a valid state

	//return TRUE;
}

