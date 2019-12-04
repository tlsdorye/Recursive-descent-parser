#include "main.h"
using namespace std;


int main()
{
	Lexing("spl_program.txt");
	getNextSymbol();
	try 
	{
		pSplProgram();
		if (next_symbol.getTokenType() == TokenType::END_OF_TOKEN)
		{
			cout << "ACCEPT\n";
			cout << toStringLeftParse(false);
		}
		else throw Error(next_symbol, "MAIN");
	}
	catch (Error error)
	{
		error.PrintErrorMessage();
	}
}