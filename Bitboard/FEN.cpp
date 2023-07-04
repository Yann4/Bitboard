#include "FEN.h"
#include "AlgebraicNotation.h"

#include <sstream>
#include <regex>

bool FromFEN(const std::string& fen, GameData& game)
{
	const std::regex fenPattern("([0-9|A-z]+)\/([0-9|A-z]+)\/([0-9|A-z]+)\/([0-9|A-z]+)\/([0-9|A-z]+)\/([0-9|A-z]+)\/([0-9|A-z]+)\/([0-9|A-z]+) ([wb]) ([-kqKQ]{1,4}) ([\-|a-z|0-9]{1,2}) ([0-9]+) ([0-9]+)", std::regex::extended);
	std::smatch results;
	if (std::regex_match(fen, results, fenPattern))
	{
		//Board layout
		int rank = 7;
		for (int fenResult = 1; fenResult <= 9; fenResult++)
		{
			int file = 0;
			for (const char c : results[fenResult].str())
			{
				if (std::isdigit(c))
				{
					file += c - '0';
				}
				else
				{
					const SquareIndex square = (rank * 8) + file;
					switch (c)
					{
					case 'p': SetPosition(game, PieceType::Pawn, Colour::White, square, true); break;
					case 'r': SetPosition(game, PieceType::Rook, Colour::White, square, true); break;
					case 'n': SetPosition(game, PieceType::Knight, Colour::White, square, true); break;
					case 'b': SetPosition(game, PieceType::Bishop, Colour::White, square, true); break;
					case 'q': SetPosition(game, PieceType::Queen, Colour::White, square, true); break;
					case 'k': SetPosition(game, PieceType::King, Colour::White, square, true); break;
					case 'P': SetPosition(game, PieceType::Pawn, Colour::Black, square, true); break;
					case 'R': SetPosition(game, PieceType::Rook, Colour::Black, square, true); break;
					case 'N': SetPosition(game, PieceType::Knight, Colour::Black, square, true); break;
					case 'B': SetPosition(game, PieceType::Bishop, Colour::Black, square, true); break;
					case 'Q': SetPosition(game, PieceType::Queen, Colour::Black, square, true); break;
					case 'K': SetPosition(game, PieceType::King, Colour::Black, square, true); break;
					}

					file++;
				}
			}

			rank--;
		}

		//Active player
		game.activeColour = results[9] == "w" ? Colour::White : Colour::Black;

		//Castle availability
		for (const char c : results[10].str())
		{
			switch (c)
			{
			case '-': memset(game.castleAvailability, 0, sizeof(game.castleAvailability)); break;
			case 'k': game.castleAvailability[Colour::White][CastleSide::Kingside] = true; break;
			case 'q': game.castleAvailability[Colour::White][CastleSide::Queenside] = true; break;
			case 'K': game.castleAvailability[Colour::Black][CastleSide::Kingside] = true; break;
			case 'Q': game.castleAvailability[Colour::Black][CastleSide::Queenside] = true; break;
			}
		}

		//En Passant
		const std::string enPassentTarget = results[11].str();
		game.enPassant = std::isalnum(enPassentTarget[0]) ? ParseSquare(enPassentTarget) : InvalidSquare;

		game.halfMove = std::atoi(results[12].str().c_str());
		game.fullMove = std::atoi(results[13].str().c_str());

		return true;
	}

	return false;
}

std::string ToFEN(const GameData& game)
{
	std::stringstream fen;

	for (int rank = 7; rank >= 0; rank--)
	{
		int consecutiveEmpty = 0;
		for (int file = 0; file < 8; file++)
		{
			const Piece piece = At(game.boards, rank, file);
			if (piece == InvalidPiece)
			{
				consecutiveEmpty++;
			}
			else
			{
				if (consecutiveEmpty != 0)
				{
					fen << consecutiveEmpty;
					consecutiveEmpty = 0;
				}

				fen << ToAlgebraic(piece);
			}
		}

		if (consecutiveEmpty != 0)
		{
			fen << consecutiveEmpty;
			consecutiveEmpty = 0;
		}

		if (rank != 0)
		{
			fen << "/";
		}
	}

	char activePlayer = (game.activeColour == Colour::White) ? 'w' : 'b';
	fen << " " << activePlayer << " ";

	bool anyCastling = false;
	if (game.castleAvailability[Colour::White][CastleSide::Kingside]) { fen << "k"; anyCastling = true; }
	if (game.castleAvailability[Colour::White][CastleSide::Queenside]) { fen << "q"; anyCastling = true; }
	if (game.castleAvailability[Colour::Black][CastleSide::Kingside]) { fen << "K"; anyCastling = true; }
	if (game.castleAvailability[Colour::Black][CastleSide::Queenside]) { fen << "Q"; anyCastling = true; }
	if (!anyCastling) { fen << "-"; }

	fen << " ";

	if (game.enPassant == InvalidSquare)
	{
		fen << "-";
	}
	else
	{
		fen << ToAlgebraic(game.enPassant);
	}

	fen << " " << game.halfMove << " " << game.fullMove;

	return fen.str();
}