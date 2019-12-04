#pragma once
#include "token.h"
#include "parser.h"
#include <string>

using namespace std;

class Error
{
public:
	string error_message;

	Error();
	Error(string message);
	Error(Token token, string procedure);
	void PrintErrorMessage();
};