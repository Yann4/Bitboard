#pragma once
#include <string>

#include "Board.h"

bool FromFEN(const std::string& fen, GameData& game);
std::string ToFEN(const GameData& game);