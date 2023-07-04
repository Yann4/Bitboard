#pragma once
#include <cstdint>

using Bitboard = uint64_t;
using SquareIndex = uint8_t;
constexpr SquareIndex InvalidSquare = -1;

enum PieceType : uint8_t
{
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King,
	Invalid
};

enum Colour : uint8_t
{
	White,
	Black
};

enum CastleSide
{
	Queenside,
	Kingside
};

using Piece = uint16_t;
constexpr Piece InvalidPiece = -1;

constexpr int NumBoards = 12;

struct GameData
{
	Bitboard boards[NumBoards];
	Colour activeColour;
	SquareIndex enPassant;
	bool castleAvailability[2][2];
	int halfMove;
	int fullMove;

	GameData();

	inline Bitboard& GetBoard(const PieceType piece, const Colour colour)
	{
		return boards[piece + (6 * colour)];
	}
	
	inline const Bitboard& GetBoard(const PieceType piece, const Colour colour) const
	{
		return boards[piece + (6 * colour)];
	}
};

//TODO: Maybe this wants to just return a Board*? 
Piece At(const Bitboard boards[NumBoards], const SquareIndex square);

inline Piece At(const Bitboard boards[NumBoards], const int rank, const int file)
{
	return At(boards, (rank * 8) + file);
}

inline void SetPosition(GameData& game, const PieceType piece, const Colour colour, const SquareIndex square, const bool setSquareActive)
{
	Bitboard& board = game.GetBoard(piece, colour);
#pragma warning(push)
#pragma warning(disable:4804) // Unsafe use of bool '-'
	const Bitboard active = static_cast<Bitboard>(-setSquareActive);
#pragma warning(pop)
	board ^= (active ^ board) & (static_cast<Bitboard>(1) << static_cast<Bitboard>(square));
}

inline void MovePieceUnchecked(GameData& game, const PieceType piece, const Colour colour, const SquareIndex from, const SquareIndex to)
{
	Bitboard& board = game.GetBoard(piece, colour);
	board ^= (0 ^ board) & (static_cast<Bitboard>(1) << static_cast<Bitboard>(from));
	board ^= (-1 ^ board) & (static_cast<Bitboard>(1) << static_cast<Bitboard>(to));
}