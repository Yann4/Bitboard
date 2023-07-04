#pragma once

#include "Board.h"
#include "MoveCalculator.h"

#include <string>
#include <array>

constexpr std::array<Bitboard, NumPositions> ValidMoves = CalculateValidMoves();

enum class MoveType : uint8_t
{
	Move,
	Capture,
	Castle,
	Promotion,
	Invalid
};

struct Move
{
	Colour side;
	Bitboard* board;
	SquareIndex startIndex;
	SquareIndex endIndex;
	Bitboard* captureBoard;
	Bitboard* promotionBoard; //When type == Castle, promotion board is set to the appropriate rook board
	MoveType type;

	Move() :
		side(Colour::White), board(nullptr), startIndex(InvalidSquare), endIndex(InvalidSquare),
		captureBoard(nullptr), promotionBoard(nullptr), type(MoveType::Invalid)
	{}

	Move(const Colour colour, Bitboard* pieceBoard, SquareIndex from, SquareIndex to) :
		side(colour), board(pieceBoard), startIndex(from), endIndex(to),
		captureBoard(nullptr), promotionBoard(nullptr), type(MoveType::Move)
	{}

	Move(const Colour colour, Bitboard* pieceBoard, SquareIndex from, SquareIndex to, Bitboard* capture) :
		side(colour), board(pieceBoard), startIndex(from), endIndex(to),
		captureBoard(capture), promotionBoard(nullptr), type(MoveType::Capture)
	{}

	Move(const Colour colour, const CastleSide castle, GameData& game) :
		side(colour), board(&game.GetBoard(PieceType::King, colour)),
		captureBoard(nullptr), promotionBoard(&game.GetBoard(PieceType::Rook, colour)), type(MoveType::Castle)
	{
		startIndex = colour == Colour::White ? 4 : 61;
		endIndex = colour == Colour::White ? (castle == CastleSide::Queenside ? 2 : 6) : (castle == CastleSide::Queenside ? 59 : 63);
	}

	Move(const Colour colour, Bitboard* pieceBoard, SquareIndex from, SquareIndex to, Bitboard* promotion, Bitboard* capture) :
		side(colour), board(pieceBoard), startIndex(from), endIndex(to),
		captureBoard(capture), promotionBoard(promotion), type(MoveType::Promotion)
	{}
};

bool IsLegalMove(const GameData& game, const std::string& alg);
bool IsLegalMove(const GameData& game, const Move& move);