#pragma once
#include "pch.h"
#include "Token.h"

namespace gedcom {
class Lexer
{
public:
	void lex(std::ifstream& stream);

private:
	void lexLine(std::ifstream& stream);
	void checkTokens(const std::string& token, const std::vector<Token>& tokens)
};
}

