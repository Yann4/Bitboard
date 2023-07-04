#include "Moves.h"
#include "AlgebraicNotation.h"

#include <regex>

bool IsLegalMove(const GameData& game, const std::string& alg)
{
	//e4 - pawn move
	//Be4 - Piece move (could also be pawn)
	//Qh4e3 - Disambiguated piece move

	//exd5 - pawn capture
	//Qxe3 - Piece capture
	//Qh4xe3 - Disambiguated piece capture

	//e8Q - Pawn promotion
	//e8=Q

	//0-0 / 0-0-0 - Castle
	//O-O / O-O-O - Castle

	std::regex movesCaptures("([PRNBQK])?([a-h|1-8]{0,2})([a-h])?x?([a-h|1-8]{2})");
	std::smatch match;
	Move move;
	if (std::regex_match(alg, match, movesCaptures))
	{
		//If 1 group, it's a pawn move
		//If 2 groups, it's either a piece move or capture, distiguished on the presence of an x
		//If 3 groups, it's either a disambiguated piece move or capture, distiguished on the presence of an x

		const SquareIndex targetSquare = ParseSquare(match[match.size() - 1].str());
		PieceType piece = PieceType::Pawn;

		if (match.size() > 1)
		{
			piece = ParsePieceType(match[0].str());
		}

		SquareIndex sourceSquare = InvalidSquare;
		if (match.size() > 2)
		{
			const std::string sourceDisambiguation = match[1].str();
			if (sourceDisambiguation.size() == 2)
			{
				sourceSquare = ParseSquare(sourceDisambiguation);
			}

			const Bitboard& board = game.GetBoard(piece, game.activeColour);
			//Find piece using either rank or file to disambiguate
		}
		else
		{
			const Bitboard& board = game.GetBoard(piece, game.activeColour);
			//Find piece using target square
		}

		const bool isCapture = alg.find('x') != std::string::npos;
	}

	return IsLegalMove(game, move);
}

bool IsLegalMove(const GameData& game, const Move& move)
{
	if (move.type == MoveType::Invalid)
	{
		return false;
	}

	return true;
}