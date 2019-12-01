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
	result += "\tleft_parse:\t";
	int count = 0, curr;
	while (!left_parse.empty())
	{
		curr = left_parse.front();
		result += " " + to_string(curr);
		left_parse.pop();
		count++;
		if (count > 10 && !left_parse.empty())
		{
			count = 0;
			result += " ->\n\t\t\t";
		}
	}
	result += "(error_point)\n\t";
	result += "expected token: " + procedure + "\n\t";
	result += "actual   token: " + token.getTokenTypeToString() + "\n";
	this->error_message = result;
}