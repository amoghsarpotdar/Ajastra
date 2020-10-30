#include <cstdio>
#include "Board.h"

#include "positionkeyprocessor.h"

U64 PieceKeys[13][120];						//Dimension[0] is for piece, dimension[1] is for the square
U64 sideKey;								//
U64 castleKeys[16];							//Four bits to represent 4 castling ways (2 ways for each side).

char PceChar[] = ".PNBRQKpnbrqk";
char SideChar[] = "wb-";
char RankChar[] = "12345678";
char FileChar[] = "abcdefgh";

int PieceBig[13] = { FALSE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, TRUE, TRUE };
int PieceMaj[13] = { FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE };
int PieceMin[13] = { FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE };
int PieceVal[13] = { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000 };
int PieceCol[13] = { BOTH, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
	BLACK, BLACK, BLACK, BLACK, BLACK, BLACK };
int PieceSlides[13] = { FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, FALSE };

int FilesBrd[BRD_SQ_NUM];
int RanksBrd[BRD_SQ_NUM];

/// <summary>
/// This function resets the board to its starting position.
/// We are setting some variables to 'invalid' state intentionally.
/// This will ensure that 'CheckBoard' will catch the invalid state of
/// board and force corrective action whn accessing board state from
/// any other class/function.
/// </summary>
/// <param name="pos"></param>
void Board::ResetBoard(S_BOARD* pos)
{
	int index;

	//Loop through the board and mark all squares as OFF_BOARD.
	//This ensures that squares around the actual board (extended area squares)
	//are not holding anything sensible value which could misguide us in
	//subsequent usage.
	for(index=0; index<BRD_SQ_NUM; ++index)
	{
		pos->pieces[index] = OFFBOARD;
	}

	//Loop through the inner squares (our real board) and mark them empty.
	for(index=0; index<64; ++index)
	{
		pos->pieces[SQ120(index)] = EMPTY;
	}

	//Reset the piece and pawns arrays to ensure they are removed.
	for(index=0;index<2;++index)
	{
		pos->bigPce[index] = 0;
		pos->majPce[index] = 0;
		pos->minPce[index] = 0;
		pos->material[index] = 0;
	}

	//The pawns array contains three pawn types -
	//White, Black and Both.
	//We need to reset the position of all three types.
	for(index = 0; index < 3; ++index)
	{
		pos->pawns[index] = 0ULL;
	}

	for(index=0; index<13; ++index)
	{
		pos->pceNum[index] = 0;
	}

	//Set both kings to position indicating 'no square'.
	pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

	pos->side = BOTH;
	pos->enPass = NO_SQ;
	pos->fiftyMovesTracker = 0;
	pos->ply = 0;
	pos->histPly = 0;
	
	pos->castlePerm = 0;
	pos->posKey = 0ULL;
}

/// <summary>
/// This function reads Foresyth-Edward Notaction based chess positions and
/// loads it into S_BOARD structure in memory.
/// Refer to https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation for more information.
/// </summary>
/// <param name="fen">Pointer to string representing FEN position</param>
/// <param name="pos">Pointer to board structure in which the position is to be loaded</param>
/// <returns>0 if successful</returns>
int Board::ParseFen(const char* fen, S_BOARD* pos)
{
	ASSERT(fen != NULL);
	ASSERT(pos != NULL);

	//We are starting with rank 8, this is bit counter-intuitive given that
	//in real life a chess board' 8th rank is where Black's pieces are (not pawns).
	//However the FEN notation starts with Black's pieces first (small letters)
	//hence we have to address the order in reverse.
	int rank = RANK_8;
	int file = FILE_A;
	int piece = 0;
	int count = 0;
	int i = 0;
	int sq64 = 0;
	int sq120 = 0;

	//Dont forget to reset board before you begin.
	ResetBoard(pos);

	//Start from the 8th rank, navigate down to the first.
	//This is because FEN notation starts with Black's pieces first.
	while((rank >= RANK_1) && *fen)
	{
		count = 1;

		switch(*fen)
		{
		case 'p': piece = bP; break;
		case 'r': piece = bR; break;
		case 'n': piece = bN; break;
		case 'b': piece = bB; break;
		case 'k': piece = bK; break;
		case 'q': piece = bQ; break;
		case 'P': piece = wP; break;
		case 'R': piece = wR; break;
		case 'N': piece = wN; break;
		case 'B': piece = wB; break;
		case 'K': piece = wK; break;
		case 'Q': piece = wQ; break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
			piece = EMPTY;
			count = *fen - '0';
			break;
		case '/':									//End of section.
		case ' ':									//End of section.
			rank--;
			file = FILE_A;
			fen++;
			continue;
		default:
			printf("FEN error \n");
			return -1;
		}

		//This loop is the tricky part. The count indicates the character
		//in FEN string that we are dealing with. [V15]
		for (i = 0; i < count; i++)
		{
			sq64 = rank * 8 + file;
			sq120 = SQ120(sq64);
			if (piece != EMPTY)
			{
				pos->pieces[sq120] = piece;
			}
			file++;
		}
		fen++;
	}

	//At this point *fen should be pointing to the field [side to move] in FEN schema.
	ASSERT(*fen == 'w' || *fen == 'b');
	pos->side = (*fen == 'w') ? WHITE : BLACK;
	fen += 2;

	//Parse castling permissions.
	for (i = 0; i < 4; i++)
	{
		if (*fen == ' ') { break; }
		
		switch (*fen)
		{
		case 'K': pos->castlePerm |= WKCA; break;
		case 'Q': pos->castlePerm |= WQCA; break;
		case 'k': pos->castlePerm |= BKCA; break;
		case 'q': pos->castlePerm |= BQCA; break;
		default: break;
		}
		fen++;
	}
	fen++;

	//TODO : Investigate why this assert fails when validating the board.
	//ASSERT(pos->castlePerm > 0 && pos->castlePerm <= 15);

	//Check the en-passant square. If we are not pointing at a hyphen
	//the FEN indicates a valid en-passant square present on the board.
	if (*fen != '-')
	{
		file = fen[0] - 'a';	//?? a = Decimal 97
		rank = fen[1] - '1';	//?? 1 = Decimal 49

		ASSERT(file >= FILE_A && file <= FILE_H);
		ASSERT(rank >= RANK_1 && rank <= RANK_8);

		pos->enPass = FR2SQ(file, rank);
	}

	//Finally generate the position key.
	positionkeyprocessor posKeyProcessor;
	pos->posKey = posKeyProcessor.GeneratePosKey(pos);

	UpdateListsMaterial(pos);
	return 0;
}

/// <summary>
/// This function prints the board on screen.
/// Along with the board and pieces, it prints file names, side-to-move,
/// en-passant status, and castling position.
/// </summary>
/// <param name="pos">Pointer to S_BOARD structure which contains the board position.</param>
void Board::PrintBoard(const S_BOARD* pos)
{
	int sq, file, rank, piece;

	printf("\nGame Board:\n\n");

	//Navigate through ranks, starting from 8th (because we want a1 square
	//on our left, and our board representation is inverted.
	for(rank=RANK_8; rank>= RANK_1; rank--)
	{
		printf("%d", rank + 1);
		//Navigate through files, starting from A to H.
		for (file = FILE_A; file <= FILE_H; file++) {
			sq = FR2SQ(file, rank);
			piece = pos->pieces[sq];
			printf("%3c", PceChar[piece]);
		}
		printf("\n");
	}
	printf("\n");

	//Print the file letters below the board.
	for(file=FILE_A; file<=FILE_H; file++)
	{
		printf("%3c", 'a' + file);
	}

	//Print other information. This includes side to move, en-pass square,
	//position key and castling permissions.
	printf("\n");
	printf("side:%c\n", SideChar[pos->side]);
	printf("enPas:%c\n", pos->enPass);				//This currently prints a decimal, will have to be converted to actual square.
	//Print castling permissions.
	printf("castle:%c%c%c%c\n",
		pos->castlePerm & WKCA ? 'K' : '-',
		pos->castlePerm & WQCA ? 'Q' : '-',
		pos->castlePerm & BKCA ? 'k' : '-',
		pos->castlePerm & BQCA ? 'q' : '-');
	printf("PosKey:%llX\n", pos->posKey);
}

/// <summary>
/// This function loops through the board, takes look at each piece, if it is not off board
/// and if it is not empty, then it updates the material list to reflect the piece.
/// This will be used to reflect changes on the board as a result of a move being played.
/// This also translates 120 square based position into 64 square position when scanning
/// through the board for pieces.
/// </summary>
/// <param name="pos"></param>
void Board::UpdateListsMaterial(S_BOARD* pos)
{
	int piece, sq, index, colour;

	for(index=0; index<BRD_SQ_NUM; ++index)
	{
		sq = index;
		piece = pos->pieces[index];
		if(piece!= OFFBOARD && piece!=EMPTY)
		{
			//Set the bit if this piece is big/major/minor piece.
			colour = PieceCol[piece];
			if (PieceBig[piece] == TRUE) pos->bigPce[colour]++;
			if (PieceMin[piece] == TRUE) pos->minPce[colour]++;
			if (PieceMaj[piece] == TRUE) pos->majPce[colour]++;

			pos->material[colour] += PieceVal[piece];
			pos->pList[piece][pos->pceNum[piece]] = sq;
			pos->pceNum[piece]++;

			//Set the bit if this is a King.
			if (piece == wK) pos->KingSq[WHITE] = sq;
			if (piece == bK) pos->KingSq[BLACK] = sq;

			//Set the bit if this is a White or Black pawn with relative position in our
			//64 square board pawns array.
			if(piece == wP)
			{
				SETBIT(pos->pawns[WHITE], SQ64(sq));
				SETBIT(pos->pawns[BOTH], SQ64(sq));
			}else if(piece == bP)
			{
				SETBIT(pos->pawns[BLACK], SQ64(sq));
				SETBIT(pos->pawns[BOTH], SQ64(sq));
			}
		}
	}
}

/// <summary>
/// This function goes through the board running checks.
/// It always returns true, however assertions check for invalid cases
/// and should throw error if any encountered.
/// </summary>
/// <param name="pos"></param>
/// <param name="bitboardproc"></param>
/// <returns></returns>
int Board::CheckBoard(const S_BOARD* pos, BitboardProcessor bitboardproc)
{
	//Temporary variables to mirror the board variables.
	int t_pceNum[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int t_bigPce[2] = { 0,0 };
	int t_majPce[2] = { 0,0 };
	int t_minPce[2] = { 0,0 };
	int t_material[2] = { 0,0 };

	int sq64, t_piece, t_pce_num, sq120, colour, pcount;

	U64 t_pawns[3] = { 0ULL, 0ULL, 0ULL };

	t_pawns[WHITE] = pos->pawns[WHITE];
	t_pawns[BLACK] = pos->pawns[BLACK];
	t_pawns[BOTH] = pos->pawns[BOTH];

	//Go through each piece on the board, compare the 64
	//square board's pieces position against 120 square
	//board's position, if not matching, throw an error.
	for(t_piece = wP; t_piece<=bK; ++t_piece)
	{
		for(t_pce_num=0; t_pce_num<pos->pceNum[t_piece];++t_pce_num)
		{
			sq120 = pos->pList[t_piece][t_pce_num];
			ASSERT(pos->pieces[sq120] == t_piece);
		}
	}

	for(sq64=0; sq64<64; ++sq64)
	{
		sq120 = SQ120(sq64);
		t_piece = pos->pieces[sq120];
		t_pceNum[t_piece]++;
		colour = PieceCol[t_piece];
		if (PieceBig[t_piece] == TRUE) t_bigPce[colour]++;
		if (PieceMin[t_piece] == TRUE) t_minPce[colour]++;
		if (PieceMaj[t_piece] == TRUE) t_majPce[colour]++;

		t_material[colour] += PieceVal[t_piece];
	}

	//This loop verifies the number of pieces of given type (e.g. Black rook, etc.)
	//If the ASSERT below fails, something has gone wrong while parsing the FEN
	//string or extracting the board position into bitboard.
	for(t_piece = wP; t_piece <=bK; ++t_piece)
	{
		ASSERT(t_pceNum[t_piece] == pos->pceNum[t_piece]);
	}

	//Check bitboards count
	//pcount = CNT(t_pawns[WHITE]);
	//bitboard board;
	positionkeyprocessor posKeyProcessor;

	//Compare the WHITE pawns on 64bit board against the pawns on 120bit board
	pcount = bitboardproc.CountBits(t_pawns[WHITE]);
	ASSERT(pcount == pos->pceNum[wP]);

	//Compare the BLACK pawns on 64bit board against the pawns on 120bit board
	pcount = bitboardproc.CountBits(t_pawns[BLACK]);
	ASSERT(pcount == pos->pceNum[bP]);

	//Compare the collection of both pawns on 64 bit board against its counterpart on 120 bit board
	pcount = bitboardproc.CountBits(t_pawns[BOTH]);
	ASSERT(pcount == (pos->pceNum[bP] + pos->pceNum[wP]));

	//Verify all WHITE pawns on 120 square board match with their
	//relevant position on 64 square board.
	while(t_pawns[WHITE])
	{
		sq64 = bitboardproc.PopBit(&t_pawns[WHITE]);
		ASSERT(pos->pieces[SQ120(sq64)] == wP);
	}

	//Verify all BLACK pawns on 120 square board match with their
	//relevant position on 64 square board.
	while(t_pawns[BLACK])
	{
		sq64 = bitboardproc.PopBit(&t_pawns[BLACK]);
		ASSERT(pos->pieces[SQ120(sq64)] == bP);
	}

	//Verify ALL pawns on 120 square board match with their
	//relevant position on 64 square board.
	while(t_pawns[BOTH])
	{
		sq64 = bitboardproc.PopBit(&t_pawns[BOTH]);
		ASSERT((pos->pieces[SQ120(sq64)] == bP) || (pos->pieces[SQ120(sq64)] == wP));
	}

	//Other sanity checks
	//Compare the arrays to ensure number of major/minor/big pieces from 64 bit board match with
	//those from 120 bit board.
	ASSERT(t_material[WHITE] == pos->material[WHITE] && t_material[BLACK] == pos->material[BLACK]);
	ASSERT(t_minPce[WHITE] == pos->minPce[WHITE] && t_minPce[BLACK] == pos->minPce[BLACK]);
	ASSERT(t_majPce[WHITE] == pos->majPce[WHITE] && t_majPce[BLACK] == pos->majPce[BLACK]);
	ASSERT(t_bigPce[WHITE] == pos->bigPce[WHITE] && t_bigPce[BLACK] == pos->bigPce[BLACK]);

	ASSERT(pos->side == WHITE || pos->side == BLACK);						//Verify that side to move is either WHITE or BLACK
	ASSERT(posKeyProcessor.GeneratePosKey(pos) == pos->posKey);				//Verify that position key is matching

	//En-Passant square validation
	ASSERT(pos->enPass == NO_SQ ||											//Either there is no en-passant square
		(RanksBrd[pos->enPass] == RANK_6 && pos->side == WHITE)				//or en passant square is on 6th rank AND it is white to move
		|| (RanksBrd[pos->enPass] == RANK_3 && pos->side == BLACK));		//or en passant square is on 3rd rank AND it is black to move

	//Verify king's position.
	ASSERT(pos->pieces[pos->KingSq[WHITE]] == wK);
	ASSERT(pos->pieces[pos->KingSq[BLACK]] == bK);

	return true;
	
}