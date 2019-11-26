#include "token.h"

map<TokenType, string> token_type_to_string =
{
	{ TokenType::EMPTY, "EMPTY" },
	{ TokenType::BEGIN, "BEGIN" },{ TokenType::END, "END" },
	{ TokenType::COMMA, "COMMA" },{ TokenType::COLON, "COLON" },{ TokenType::SEMICOLON, "SEMICOLON" },{ TokenType::DOT, "DOT" },
	{ TokenType::LABEL, "LABEL" },{ TokenType::INTEGER, "INTEGER" },
	{ TokenType::ASSIGN, "ASSIGN" },{ TokenType::GOTO, "GOTO" },
	{ TokenType::IF, "IF" },{ TokenType::THEN, "THEN" },{ TokenType::ELSE, "ELSE" },{ TokenType::FI, "FI" },
	{ TokenType::OPEN_PAREN, "OPEN_PAREN" },{ TokenType::CLOSE_PAREN, "CLOSE_PAREN" },
	{ TokenType::LESS, "LESS" },{ TokenType::MORE, "MORE" },{ TokenType::EQ, "EQ" },
	{ TokenType::ADD, "ADD" },{ TokenType::SUB, "SUB" },{ TokenType::MUL, "MUL" },{ TokenType::DIV, "DIV" },
	{ TokenType::INPUT, "INPUT" },{ TokenType::OUTPUT, "OUTPUT" },
	{ TokenType::NUMBER, "NUMBER" },{ TokenType::IDENTIFIER, "IDENTIFIER" },
	{ TokenType::END_OF_TOKEN, "END_OF_TOKEN" }
};

Token::Token()
{

}

Token::Token(TokenType token_type, string syntax)
{
	this->token_type = token_type;
	this->syntax = syntax;
}

string Token::getSyntax()
{
	return syntax;
}

TokenType Token::getTokenType()
{
	return token_type;
}

string Token::getTokenTypeToString()
{
	auto it = token_type_to_string.find(this->token_type);
	if (it == token_type_to_string.end()) return "UNDEFINED";
	return it->second;
}
