#include <iostream>

#include "Board.h"
#include "FEN.h"


int main(int argc, char** argv)
{
	GameData game;
	const std::string starting = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w kqKQ - 0 1";
	FromFEN(starting, game);
	const std::string ending = ToFEN(game);
}