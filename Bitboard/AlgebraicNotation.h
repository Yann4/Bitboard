#pragma once
#include <string>
#include "Board.h"

char ToAlgebraic(const Piece piece);
inline SquareIndex ParseSquare(const std::string& alg)
{
	const int file = std::tolower(alg[0]) - 'a';
	const int rank = alg[1] - '1';
	return (rank * 8) + file;
}
inline PieceType ParsePieceType(const std::string& alg)
{
	if (alg.empty())
	{
		return PieceType::Invalid;
	}

	switch (std::toupper(alg[0]))
	{
	case 'P': return PieceType::Pawn;
	case 'R': return PieceType::Rook;
	case 'N': return PieceType::Knight;
	case 'B': return PieceType::Bishop;
	case 'Q': return PieceType::Queen;
	case 'K': return PieceType::King;
	default: return PieceType::Invalid;
	}
}

namespace
{
	constexpr std::string_view squareNames[] =
	{
		"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
		"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
		"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
		"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
		"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
		"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
		"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
		"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
	};
}

inline constexpr std::string_view ToAlgebraic(const SquareIndex square)
{
	return squareNames[square];
}