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

/*
1 : <spl_program>	::= <block> '.'
*/
void pSplProgram()
{
	left_parse.push(1);
	pBlock();
	pDot();
}

/*
2 : <block>			::= 'begin' <A> <st_list> 'end'
3 : <A>				::= <dcl> ';' <A>
4 :					  | e
*/
void pBlock()
{
	bool flag = false;
	left_parse.push(2);
	pBegin();
	while (next_symbol.getTokenType() == TokenType::LABEL
		|| next_symbol.getTokenType() == TokenType::INTEGER)
	{
		flag = true;
		left_parse.push(3);
		pDcl();
		pSemicolon();
	}
	if(!flag) left_parse.push(4);
	pStList();
	pEnd();
}

/*
5 : <dcl>			::= 'label' <id> <B>
6 :					  | 'integer' <id> <B>
7 : <B>				::= ',' <id>
8 :					  | e
*/
void pDcl()
{
	bool flag = false;
	if (next_symbol.getTokenType() == TokenType::LABEL)
	{
		left_parse.push(5);
		getNextSymbol();
	}
	else if (next_symbol.getTokenType() == TokenType::INTEGER)
	{
		left_parse.push(6);
		getNextSymbol();
	}
	else throw Error(next_symbol, "LABEL or INTEGER");

	pIdentifier();
	while (next_symbol.getTokenType() == TokenType::COMMA)
	{
		flag = true;
		left_parse.push(7);
		getNextSymbol();
		pIdentifier();
	}
	if(!flag) left_parse.push(8);
}

/*
9 : <st_list>		::= <st> <C>
10: <C>				::= ',' <st> <C>
11:					  | e
*/
void pStList()
{
	bool flag = false;
	left_parse.push(9);
	pSt();
	while (next_symbol.getTokenType() == TokenType::SEMICOLON)
	{
		flag = true;
		left_parse.push(10);
		getNextSymbol();
		pSt();
	}
	if(!flag) left_parse.push(11);
}

/*
12: <st>			::= <id> ':' <statement>
13:					  | <statement>
*/
void pSt()
{
	bool flag = false;
	// statement 의 assignment 의 first가 id가 올수 있으므로 2개까지 봐야함 --> LL(2)로
	if (next_symbol.getTokenType() == TokenType::IDENTIFIER && buffer.front().getTokenType() == TokenType::COLON)
	{
		flag = true;
		left_parse.push(12);
		getNextSymbol();
		getNextSymbol();
	}
	if(!flag) left_parse.push(13);
	pStatement();
}

/*
14: <statement>		::= <assignment>
15:					  | <goto_st>
16:					  | <if_st>
17:					  | <write_st>
18:					  | <block>
*/
void pStatement()
{
	if (next_symbol.getTokenType() == TokenType::INPUT
		|| next_symbol.getTokenType() == TokenType::IDENTIFIER
		|| next_symbol.getTokenType() == TokenType::NUMBER
		|| next_symbol.getTokenType() == TokenType::OPEN_PAREN)
		left_parse.push(14), pAssignment();
	else if (next_symbol.getTokenType() == TokenType::GOTO) 
		left_parse.push(15), pGotoStatement();
	else if (next_symbol.getTokenType() == TokenType::IF) 
		left_parse.push(16), pIfStatement();
	else if (next_symbol.getTokenType() == TokenType::OUTPUT) 
		left_parse.push(17), pWriteStatement();
	else if (next_symbol.getTokenType() == TokenType::BEGIN) 
		left_parse.push(18), pBlock();
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