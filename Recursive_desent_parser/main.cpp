#include "main.h"
using namespace std;


int main()
{
	//TextLexing("lexer_test.txt");
	Lexing("spl_program.txt");
	getNextSymbol();
	try 
	{
		pSplProgram();
		if (next_symbol.getTokenType() == TokenType::END_OF_TOKEN)
			cout << "ACCEPT\n";
		else throw Error(next_symbol, "MAIN");
	}
	catch (Error error)
	{
		cout << error.error_message << "\n";
	}
}