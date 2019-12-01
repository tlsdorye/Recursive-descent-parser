#include "parser.h"

Token next_symbol;

queue<int> left_parse;

string toStringLeftParse(bool error)
{
	string result = "";
	result += "left_parse:\t";
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
			result += " ->\n\t\t";
		}
	}
	if(error) result += " / (error_point)\n";
	else result += "\n";
	return result;
}

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
10: <C>				::= ';' <st> <C>
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

/*
19:	<assignment>	::= <exp> '=>' <id> <D>
20: <D>				::= '=>' <id> <D>
21:					  | e
*/
void pAssignment()
{
	bool flag = false;
	left_parse.push(19);
	pExpr();
	pAssign();
	pIdentifier();
	while (next_symbol.getTokenType() == TokenType::ASSIGN)
	{
		flag = true;
		left_parse.push(20);
		getNextSymbol();
		pIdentifier();
	}
	if (!flag) left_parse.push(21);
}

/*
22: <goto_st>		::= 'goto' <id>
*/
void pGotoStatement()
{
	left_parse.push(22);
	pGoto();
	pIdentifier();
}

/*
23: <if_st>			::= 'if' <condition> 'then' <st_list> <else> 'fi'
24: <else>			::= 'else' <st_list>
25:					  | e
*/
void pIfStatement()
{
	bool flag = false;
	left_parse.push(23);
	pIf();
	pCondition();
	pThen();
	pStList();
	if (next_symbol.getTokenType() == TokenType::ELSE)
	{
		flag = true;
		left_parse.push(24);
		pStList();
	}
	if (!flag) left_parse.push(25);
	pFi();
}

/*
26: <write_st>		::= 'output' '(' <exp> <E> ')'
27: <E>				::= ',' <exp> <E>
28:					  | e
*/
void pWriteStatement()
{
	bool flag = false;
	left_parse.push(26);
	pOutput();
	pOpenParen();
	pExpr();
	while (next_symbol.getTokenType() == TokenType::COMMA)
	{
		flag = true;
		left_parse.push(27);
		pExpr();
	}
	if (!flag) left_parse.push(28);
	pCloseParen();
}

/*
29: <condition>		::= <exp> <F> <exp>
30: <F>				::= '<'
31:					  | '>'
32:					  | '='
*/
void pCondition()
{
	left_parse.push(29);
	pExpr();
	if (next_symbol.getTokenType() == TokenType::LESS)
		left_parse.push(30);
	else if (next_symbol.getTokenType() == TokenType::MORE)
		left_parse.push(31);
	else if (next_symbol.getTokenType() == TokenType::EQ)
		left_parse.push(32);
	else throw Error(next_symbol, "CONDITION");
	getNextSymbol();
	pExpr();
}

/*
33: <exp>			::= <term> <G>
34: <G>				::= '+' <term> <G>
35:					  | '-' <term> <G>
36:					  | e
*/
void pExpr()
{
	bool flag = false;
	left_parse.push(33);
	pTerm();
	while (next_symbol.getTokenType() == TokenType::ADD
		|| next_symbol.getTokenType() == TokenType::SUB)
	{
		flag = true;
		if (next_symbol.getTokenType() == TokenType::ADD)
			left_parse.push(34);
		else left_parse.push(35);
		getNextSymbol();
		pTerm();
	}
	if (!flag) left_parse.push(36);
}

/*
37: <term>			::= <factor> <H>
38: <H>				::= '*' <factor> <H>
39:					  | '/' <factor> <H>
40:					  | e
*/
void pTerm()
{
	bool flag = false;
	left_parse.push(37);
	pFactor();
	while (next_symbol.getTokenType() == TokenType::MUL
		|| next_symbol.getTokenType() == TokenType::DIV)
	{
		flag = true;
		if (next_symbol.getTokenType() == TokenType::MUL)
			left_parse.push(38);
		else left_parse.push(39);
		getNextSymbol();
		pFactor();
	}
	if (!flag) left_parse.push(40);
}

/*
41: <factor>		::= 'input
42:					  | <id>
43:					  | <number>
44:					  | '(' <exp> ')'
*/
void pFactor()
{
	if (next_symbol.getTokenType() == TokenType::INPUT)
		left_parse.push(41), getNextSymbol();
	else if (next_symbol.getTokenType() == TokenType::IDENTIFIER)
		left_parse.push(42), getNextSymbol();
	else if (next_symbol.getTokenType() == TokenType::NUMBER)
		left_parse.push(43), getNextSymbol();
	else if (next_symbol.getTokenType() == TokenType::OPEN_PAREN)
	{
		left_parse.push(44);
		getNextSymbol();
		pExpr();
		pCloseParen();
	}
	else throw Error(next_symbol, "FACTOR");
}