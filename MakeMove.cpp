#include "MakeMove.h"

#include "Validator.h"

//Hashing macros
#define HASH_PCE(pce,sq) (pos->posKey ^= (PieceKeys[(pce)][(sq)]))			//Hashing piece
#define HASH_CA (pos->posKey ^= (CastleKeys[(pos->castlePerm)]))			//Hashing castling permissions
#define HASH_SIDE (pos->poskey ^= (sideKey))								//Hashing side to move
#define HASH_EP (pos->posKey ^= (PieceKeys[EMPTY][(pos->enPass)]))			//Hashing en-passant square


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
	for(index=0; index<pos->pceNum[pce];++index)
	{
		if(pos->pList[pce][index] == sq)
		{
			t_pceNum = index;
			break;
		}
	}

	ASSERT(t_pceNum != -1);

	pos->pceNum[pce]--;													//Since we are removing a piece, update the value to reflect change in count
	pos->pList[pce][t_pceNum] = pos->pList[pce][pos->pceNum[pce]];		//Refer to V39 if this becomes confusing
}

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

void MakeMove::MovePiece(int from, int to, S_BOARD* pos)
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
			pos->pList[pce][index] = 0;
#ifdef DEBUG
			t_PieceNum = TRUE;											//If this assert fails, that means our pList array is not aligned with actual piece positions
#endif
			break;
		}
	}
	ASSERT(t_PieceNum);
}


