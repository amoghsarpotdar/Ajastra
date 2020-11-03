#include "Validator.h"

#include "defs.h"

/// <summary>
/// Returns true if file rank is between 0 and 7 (i.e., it is on our chessboard)
/// </summary>
/// <param name="fr">Constant integer pointer pointing to file rank</param>
/// <returns>0 If valid, 1 if invalid</returns>
int Validator::FileRankValid(const int fr)
{
	return (fr >= 0 && fr <= 7) ? 1 : 0;
}

/// <summary>
/// Returns true if piece value is in the range of 1 to 12, i.e. piece is either
/// a White or Black, valid piece.
/// </summary>
/// <param name="pce">Constant integer value indicating piece type number</param>
/// <returns>1 if valid piece, otherwise 1, i.e. false</returns>
int Validator::PieceValid(const int pce)
{
	return (pce >= wP && pce <= bK) ? 1 : 0;
}

/// <summary>
/// Returns true if piece value is not empty and is of type of Black King.
/// </summary>
/// <param name="pce">Constant integer value indicating piece type number</param>
/// <returns>1 if piece is not empty and of value of valid piece</returns>
int Validator::PieceValidEmpty(const int pce)
{
	return (pce >= EMPTY && pce <= bK) ? 1 : 0;
}

/// <summary>
/// Returns true if supplied integer indicates valid BLACK or WHITE piece value.
/// </summary>
/// <param name="side">Constant integer indicating side to move (WHITE OR BLACK)</param>
/// <returns></returns>
int Validator::SideValid(const int side)
{
	return (side == WHITE || side == BLACK) ? 1 : 0;
}

/// <summary>
/// Returns true if supplied square points to a board which is in the range of 'ON-BOARD' squares.
/// Refer to Notes.txt for more information. OFF BOARD squares are indicated by integer value 100.
/// </summary>
/// <param name="sq">Constant integer pointing to square index</param>
/// <returns>True if square value is 100 (i.e. OFF BOARD).</returns>
int Validator::SqOnBoard(const int sq)
{
	return FilesBrd[sq] == OFFBOARD ? 0 : 1;
}





