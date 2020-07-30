#include <stdio.h>
#include "Board.h"

#include "positionkeyprocessor.h"

U64 PieceKeys[13][120];						//Dimension[0] is for piece, dimension[1] is for the square
U64 sideKey;								//
U64 castleKeys[16];							//Four bits to represent 4 castling ways (2 ways for each side).

char PceChar[] = ".PNBRQKpnbrqk";
char SideChar[] = "wb-";
char RankChar[] = "12345678";
char FileChar[] = "abcdefgh";

void Board::ResetBoard(S_BOARD* pos)
{
	int index = 0;

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

	//Reset the piece arrays to ensure they are removed.
	for(index=0;index<3;++index)
	{
		pos->bigPce[index] = 0;
		pos->majPce[index] = 0;
		pos->minPce[index] = 0;
		pos->pawns[index] = 0ULL;
	}

	for(index=0; index<13; ++index)
	{
		pos->pceNum[index] = 0;
	}

	//Set kings to position indicating 'no square'.
	pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

	pos->side = BOTH;
	pos->enPass = NO_SQ;
	pos->fiftyMovesTracker = 0;
	pos->ply = 0;
	pos->castlePerm = 0;
	pos->posKey = 0ULL;
}

int Board::Parse_Fen(const char* fen, S_BOARD* pos)
{
	ASSERT(fen != NULL);
	ASSERT(pos != NULL);

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

	ASSERT(pos->castlePerm > 0 && pos->castlePerm <= 15);

	if (*fen != '-')
	{
		file = fen[0] - 'a';	//?? a = Decimal 97
		rank = fen[1] - '1';	//?? 1 = Decimal 49

		ASSERT(file >= FILE_A && file <= FILE_H);
		ASSERT(rank >= RANK_1 && rank <= RANK_8);

		pos->enPass = FR2SQ(file, rank);
	}
	
	positionkeyprocessor posKeyProcessor;
	pos->posKey = posKeyProcessor.GeneratePosKey(pos);

	return 0;
}

void Board::PrintBoard(const S_BOARD* pos)
{
	int sq, file, rank, piece;

	printf("\nGame Board:\n\n");

	//Navigate through ranks, starting from 8th (because we want a1 square
	//on our left.
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

	for(file=FILE_A; file<=FILE_H; file++)
	{
		printf("%3c", 'a' + file);
	}
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


