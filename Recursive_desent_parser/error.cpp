#include "error.h"

Error::Error()
{

}

Error::Error(Token token, string procedure)
{
	string message = "error - procedure " + procedure;
	message += ", [" + token.getTokenTypeToString() + ", " + token.getSyntax() + " ]";
	this->error_message = message;
}