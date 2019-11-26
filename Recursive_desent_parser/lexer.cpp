#include "lexer.h"

queue<Token> buffer;

map<string, function<Token(string)>> regex_to_token =
{
	{ "[ \t\n]", [](string text)->Token {return Token(TokenType::EMPTY, text); } },
	{ "begin", [](string text)->Token {return Token(TokenType::BEGIN, text); } },
	{ "end", [](string text)->Token {return Token(TokenType::END, text); } },
	{ "input", [](string text)->Token {return Token(TokenType::INPUT, text); } },
	{ "output", [](string text)->Token {return Token(TokenType::OUTPUT, text); } },
	{ "label", [](string text)->Token {return Token(TokenType::LABEL, text); } },
	{ "integer", [](string text)->Token {return Token(TokenType::INTEGER, text); } },
	{ "goto", [](string text)->Token {return Token(TokenType::GOTO, text); } },
	{ "if", [](string text)->Token {return Token(TokenType::IF, text); } },
	{ "then", [](string text)->Token {return Token(TokenType::THEN, text); } },
	{ "else", [](string text)->Token {return Token(TokenType::ELSE, text); } },
	{ "fi", [](string text)->Token {return Token(TokenType::FI, text); } },
	{ "\\,", [](string text)->Token {return Token(TokenType::COMMA, text); } },
	{ "\\:", [](string text)->Token {return Token(TokenType::COLON, text); } },
	{ "\\;", [](string text)->Token {return Token(TokenType::SEMICOLON, text); } },
	{ "\\.", [](string text)->Token {return Token(TokenType::DOT, text); } },
	{ "=>", [](string text)->Token {return Token(TokenType::ASSIGN, text); } },
	{ "\\(", [](string text)->Token {return Token(TokenType::OPEN_PAREN, text); } },
	{ "\\)", [](string text)->Token {return Token(TokenType::CLOSE_PAREN, text); } },
	{ "<", [](string text)->Token {return Token(TokenType::LESS, text); } },
	{ ">", [](string text)->Token {return Token(TokenType::MORE, text); } },
	{ "\\=", [](string text)->Token {return Token(TokenType::EQ, text); } },
	{ "\\+", [](string text)->Token {return Token(TokenType::ADD, text); } },
	{ "\\-", [](string text)->Token {return Token(TokenType::SUB, text); } },
	{ "\\*", [](string text)->Token {return Token(TokenType::MUL, text); } },
	{ "\\/", [](string text)->Token {return Token(TokenType::DIV, text); } },
	{ "[0-9]+", [](string text)->Token {return Token(TokenType::NUMBER, text); } },
	{ "\\$", [](string text)->Token {return Token(TokenType::END_OF_TOKEN, text); } }
};

void Lexing(const string filepath)
{
	ifstream reader = ifstream(filepath);
	if (reader.is_open())
	{
		string line;
		while (getline(reader, line))
			Matching(line);
	}
	else throw Error(Token(), "FILE NOT OPEN");
}

void Matching(string line)
{
	smatch match_result;
	while (line != "")
	{
		bool matched = false;
		for (auto it : regex_to_token)
		{
			regex curr_regex = regex(it.first);
			if (regex_search(line, match_result, curr_regex) && match_result.prefix() == "")
			{
				if (it.second(match_result[0]).getTokenType() != TokenType::EMPTY)
					buffer.push(it.second(match_result[0]));
				line = match_result.suffix();
				matched = true;
				break;
			}
		}
		if (!matched)
		{
			regex id_regex("[a-zA-Z]+[a-zA-Z0-9]*");
			if (regex_search(line, match_result, id_regex) && match_result.prefix() == "")
			{
				buffer.push(Token(TokenType::IDENTIFIER, match_result[0]));
				line = match_result.suffix();
				matched = true;
			}
			else throw Error(Token(), "NO MATCHING");
		}
	}
}

void TextLexing(const string filepath)
{
	Lexing(filepath);
	cout << buffer.size() << "\n";
	while (!buffer.empty())
	{
		Token top = buffer.front();
		cout << "TokenType: " << top.getTokenTypeToString();
		cout << ", Syntax: " << top.getSyntax() << "\n";
		buffer.pop();
	}
}