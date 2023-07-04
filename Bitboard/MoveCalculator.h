#pragma once

#include <array>
#include "Board.h"

constexpr size_t NumPositions = 64 * 6;
using PositionMap = std::array<Bitboard, NumPositions>;

constexpr PositionMap CalculateValidMoves()
{
	PositionMap positions{};
	
	return positions;
}
