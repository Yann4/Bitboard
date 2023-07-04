#include "Board.h"
#include <memory>

GameData::GameData()
{
	memset(boards, 0, sizeof(boards));
	activeColour = Colour::White;
	enPassant = InvalidSquare;
	memset(castleAvailability, 0, sizeof(castleAvailability));
	halfMove = 0;
	fullMove = 0;
}

Piece At(const Bitboard boards[NumBoards], const SquareIndex square)
{
	for (int board = 0; board < NumBoards; board++)
	{
		if (((boards[board] >> square) & 0x1) == 0x1)
		{
			Piece piece = board < 6 ? Colour::White : Colour::Black;
			piece |= (board < 6 ? board : board - 6) << 8;
			return piece;
		}
	}

	return InvalidPiece;
}