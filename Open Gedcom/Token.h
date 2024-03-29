#pragma once
#include "pch.h"

namespace gedcom {
enum class TokenType {

};

class Token {
	TokenType type;
	std::string value;
	std::vector<Token> ChildTokens{};
};
}
