#include "error.h"

Error::Error()
{

}

Error::Error(string message)
{
	string result = "error - " + message;
	this->error_message = message;
}

Error::Error(Token token, string procedure)
{
	string result = "error - parsing\n";
	result += "\texpected token: " + procedure + "\n\t";
	result += "actual   token: " + token.getTokenTypeToString() + "\n";
	this->error_message = result;
}

void Error::PrintErrorMessage()
{
	cout << this->error_message << "\n";
	cout << toStringLeftParse(true);
}