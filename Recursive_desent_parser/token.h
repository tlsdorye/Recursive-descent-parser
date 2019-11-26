#pragma once
#include <map>
#include <string>
using namespace std;

enum class TokenType
{
	EMPTY,
	BEGIN, END,
	COMMA, COLON, SEMICOLON, DOT,
	LABEL, INTEGER,
	ASSIGN, GOTO,
	IF, THEN, ELSE, FI,
	OPEN_PAREN, CLOSE_PAREN,
	LESS, MORE, EQ,
	ADD, SUB, MUL, DIV,
	INPUT, OUTPUT,
	NUMBER, IDENTIFIER,
	END_OF_TOKEN
};

class Token
{
private:
	TokenType token_type;
	string syntax;
public:
	Token();
	Token(TokenType token_type, string syntax);
	string getSyntax();
	TokenType getTokenType();
	string getTokenTypeToString();
};

extern map<TokenType, string> token_to_string;