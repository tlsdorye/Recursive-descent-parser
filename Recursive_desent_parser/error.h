#pragma once
#include "token.h"
#include <string>
using namespace std;

class Error
{
public:
	string error_message;

	Error();
	Error(Token token, string procedure);
};

