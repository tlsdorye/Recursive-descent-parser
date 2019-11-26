#include "parser.h"

Token next_symbol;

queue<int> left_parse;

void getNextSymbol()
{
	next_symbol = buffer.front();
	buffer.pop();
}

void pBegin()
{
	if (next_symbol.getTokenType() == TokenType::BEGIN)
		getNextSymbol();
	else throw Error(next_symbol, "BEGIN");
}

void pEnd()
{
	if (next_symbol.getTokenType() == TokenType::END)
		getNextSymbol();
	else throw Error(next_symbol, "END");
}

void pComma()
{
	if (next_symbol.getTokenType() == TokenType::COMMA)
		getNextSymbol();
	else throw Error(next_symbol, "COMMA");
}

void pColon()
{
	if (next_symbol.getTokenType() == TokenType::COLON)
		getNextSymbol();
	else throw Error(next_symbol, "COLON");
}

void pSemicolon()
{
	if (next_symbol.getTokenType() == TokenType::SEMICOLON)
		getNextSymbol();
	else throw Error(next_symbol, "SEMICOLON");
}

void pDot()
{
	if (next_symbol.getTokenType() == TokenType::DOT)
		getNextSymbol();
	else throw Error(next_symbol, "DOT");
}

void pLabel()
{
	if (next_symbol.getTokenType() == TokenType::LABEL)
		getNextSymbol();
	else throw Error(next_symbol, "LABEL");
}

void pInteger()
{
	if (next_symbol.getTokenType() == TokenType::INTEGER)
		getNextSymbol();
	else throw Error(next_symbol, "INTEGER");
}

void pAssign()
{
	if (next_symbol.getTokenType() == TokenType::ASSIGN)
		getNextSymbol();
	else throw Error(next_symbol, "ASSIGN");
}

void pGoto()
{
	if (next_symbol.getTokenType() == TokenType::GOTO)
		getNextSymbol();
	else throw Error(next_symbol, "GOTO");
}

void pIf()
{
	if (next_symbol.getTokenType() == TokenType::IF)
		getNextSymbol();
	else throw Error(next_symbol, "IF");
}

void pThen()
{
	if (next_symbol.getTokenType() == TokenType::THEN)
		getNextSymbol();
	else throw Error(next_symbol, "THEN");
}

void pElse()
{
	if (next_symbol.getTokenType() == TokenType::ELSE)
		getNextSymbol();
	else throw Error(next_symbol, "ELSE");
}

void pFi()
{
	if (next_symbol.getTokenType() == TokenType::FI)
		getNextSymbol();
	else throw Error(next_symbol, "FI");
}

void pOpenParen()
{
	if (next_symbol.getTokenType() == TokenType::OPEN_PAREN)
		getNextSymbol();
	else throw Error(next_symbol, "OPEN_PAREN");
}

void pCloseParen()
{
	if (next_symbol.getTokenType() == TokenType::CLOSE_PAREN)
		getNextSymbol();
	else throw Error(next_symbol, "CLOSE_PAREN");
}

void pLess()
{
	if (next_symbol.getTokenType() == TokenType::LESS)
		getNextSymbol();
	else throw Error(next_symbol, "LESS");
}

void pMore()
{
	if (next_symbol.getTokenType() == TokenType::MORE)
		getNextSymbol();
	else throw Error(next_symbol, "MORE");
}

void pEq()
{
	if (next_symbol.getTokenType() == TokenType::EQ)
		getNextSymbol();
	else throw Error(next_symbol, "EQ");
}

void pAdd()
{
	if (next_symbol.getTokenType() == TokenType::ADD)
		getNextSymbol();
	else throw Error(next_symbol, "ADD");
}

void pSub()
{
	if (next_symbol.getTokenType() == TokenType::SUB)
		getNextSymbol();
	else throw Error(next_symbol, "SUB");
}

void pMul()
{
	if (next_symbol.getTokenType() == TokenType::MUL)
		getNextSymbol();
	else throw Error(next_symbol, "MUL");
}

void pDiv()
{
	if (next_symbol.getTokenType() == TokenType::DIV)
		getNextSymbol();
	else throw Error(next_symbol, "DIV");
}

void pInput()
{
	if (next_symbol.getTokenType() == TokenType::INPUT)
		getNextSymbol();
	else throw Error(next_symbol, "INPUT");
}

void pOutput()
{
	if (next_symbol.getTokenType() == TokenType::OUTPUT)
		getNextSymbol();
	else throw Error(next_symbol, "OUTPUT");
}

void pNumber()
{
	if (next_symbol.getTokenType() == TokenType::NUMBER)
		getNextSymbol();
	else throw Error(next_symbol, "NUMBER");
}

void pIdentifier()
{
	if (next_symbol.getTokenType() == TokenType::IDENTIFIER)
		getNextSymbol();
	else throw Error(next_symbol, "IDENTIFIER");
}

//<spl_program>		::= <block> '.'
void pSplProgram()
{
	left_parse.push(1);
	pBlock();
	pDot();
}

//<block>			:: = 'begin' { <dcl> ';' } <st_list> 'end'
void pBlock()
{
	left_parse.push(2);
	pBegin();
	while (next_symbol.getTokenType() == TokenType::LABEL
		|| next_symbol.getTokenType() == TokenType::INTEGER)
	{
		pDcl();
		pSemicolon();
	}
	pStList();
	pEnd();
}

//<dcl>				:: = ('label' | 'integer') <id> { ',' <id> }
void pDcl()
{
	cout << 3 << "\n";
	if (next_symbol.getTokenType() == TokenType::LABEL
		|| next_symbol.getTokenType() == TokenType::INTEGER)
		getNextSymbol();
	else throw Error(next_symbol, "DCL");

	pIdentifier();
	while (next_symbol.getTokenType() == TokenType::COMMA)
	{
		getNextSymbol();
		pIdentifier();
	}
}

//<st_list>			:: = <st> { ',' <st> }
void pStList()
{
	cout << 4 << "\n";
	pSt();
	while (next_symbol.getTokenType() == TokenType::SEMICOLON)
	{
		getNextSymbol();
		pSt();
	}
}

//<st>				:: = [<id> ':'] <statement>
void pSt()
{
	cout << 5 << "\n";
	// statement 의 assignment 의 first가 id가 올수 있으므로 2개까지 봐야함 --> LL(2)로
	if (next_symbol.getTokenType() == TokenType::IDENTIFIER && buffer.front().getTokenType() == TokenType::COLON)
	{
		getNextSymbol();
		getNextSymbol();
	}
	//getNextSymbol();
	pStatement();
}

//<statement>		:: = <assignment> | <goto_st> | <if_st> | <write_st> | <block>
void pStatement()
{
	cout << 6 << "\n";
	if (next_symbol.getTokenType() == TokenType::INPUT
		|| next_symbol.getTokenType() == TokenType::IDENTIFIER
		|| next_symbol.getTokenType() == TokenType::NUMBER
		|| next_symbol.getTokenType() == TokenType::OPEN_PAREN)
		pAssignment();
	else if (next_symbol.getTokenType() == TokenType::GOTO) pGotoStatement();
	else if (next_symbol.getTokenType() == TokenType::IF) pIfStatement();
	else if (next_symbol.getTokenType() == TokenType::OUTPUT) pWriteStatement();
	else if (next_symbol.getTokenType() == TokenType::BEGIN) pBlock();
	else throw Error(next_symbol, "STATEMENT");
}

// <assignment>		::= <exp> '=>' <id> { '=>' <id> }
void pAssignment()
{
	cout << 7 << "\n";
	pExpr();
	pAssign();
	pIdentifier();
	while (next_symbol.getTokenType() == TokenType::ASSIGN)
	{
		getNextSymbol();
		pIdentifier();
	}
}

//<goto_st>			:: = 'goto' <id>
void pGotoStatement()
{
	cout << 8 << "\n";
	pGoto();
	pIdentifier();
}

//<if_st>			::= 'if' <condition> 'then' <st_list> [ 'else' <st_list> ] 'fi'
void pIfStatement()
{
	cout << 9 << "\n";
	pIf();
	pCondition();
	pThen();
	pStList();
	if (next_symbol.getTokenType() == TokenType::ELSE) pStList();
	pFi();
}

//<write_st>		::= 'output' '(' <exp> { ',' <exp> } ')'
void pWriteStatement()
{
	cout << 10 << "\n";
	pOutput();
	pOpenParen();
	pExpr();
	while (next_symbol.getTokenType() == TokenType::COMMA) pExpr();
	pCloseParen();
}

//<condition>		:: = <exp> ('<' | '>' | '=') <exp>
void pCondition()
{
	cout << 11 << "\n";
	pExpr();
	if (next_symbol.getTokenType() == TokenType::LESS
		|| next_symbol.getTokenType() == TokenType::MORE
		|| next_symbol.getTokenType() == TokenType::EQ)
		getNextSymbol();
	else throw Error(next_symbol, "CONDITION");
	pExpr();
}

//<exp>				:: = <term> { ('+' | '-') <term> }
void pExpr()
{
	cout << 12 << "\n";
	pTerm();
	while (next_symbol.getTokenType() == TokenType::ADD
		|| next_symbol.getTokenType() == TokenType::SUB)
	{
		getNextSymbol();
		pTerm();
	}
}

//<term>			:: = <factor> { ('*' | '/') <factor> }
void pTerm()
{
	cout << 13 << "\n";
	pFactor();
	while (next_symbol.getTokenType() == TokenType::MUL
		|| next_symbol.getTokenType() == TokenType::DIV)
	{
		getNextSymbol();
		pFactor();
	}
}

//<factor>			:: = 'input' | <id> | <number> | '(' <exp> ')'
void pFactor()
{
	cout << 14 << "\n";
	if (next_symbol.getTokenType() == TokenType::INPUT
		|| next_symbol.getTokenType() == TokenType::IDENTIFIER
		|| next_symbol.getTokenType() == TokenType::NUMBER
		)
		getNextSymbol();
	else if (next_symbol.getTokenType() == TokenType::OPEN_PAREN)
	{
		pExpr();
		pCloseParen();
	}
	else throw Error(next_symbol, "FACTOR");
}