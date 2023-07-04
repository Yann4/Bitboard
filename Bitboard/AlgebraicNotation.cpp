#include "AlgebraicNotation.h"

char ToAlgebraic(const Piece piece)
{
	const Colour colour = static_cast<Colour>(piece & 0x00FF);
	switch (static_cast<PieceType>(piece >> 8))
	{
	case PieceType::Pawn: return colour == Colour::White ? 'p' : 'P';
	case PieceType::Rook: return colour == Colour::White ? 'r' : 'R';
	case PieceType::Knight: return colour == Colour::White ? 'n' : 'N';
	case PieceType::Bishop: return colour == Colour::White ? 'b' : 'B';
	case PieceType::Queen: return colour == Colour::White ? 'q' : 'Q';
	case PieceType::King: return colour == Colour::White ? 'k' : 'K';
	}

	return 'X';
}