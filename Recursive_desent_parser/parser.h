#pragma once
#include "token.h"
#include "lexer.h"
#include <queue>

extern Token next_symbol;

extern queue<int> left_parse;

void getNextSymbol();

// Terminal procedure
void pBegin();

void pEnd();

void pComma();

void pColon();

void pSemicolon();

void pDot();

void pLabel();

void pInteger();

void pAssign();

void pGoto();

void pIf();

void pThen();

void pElse();

void pFi();

void pOpenParen();

void pCloseParen();

void pLess();

void pMore();

void pEq();

void pAdd();

void pSub();

void pMul();

void pDiv();

void pInput();

void pOutput();

void pNumber();

void pIdentifier();

//Nonterminal
void pSplProgram();

void pBlock();

void pDcl();

void pStList();

void pSt();

void pStatement();

void pAssignment();

void pGotoStatement();

void pIfStatement();

void pWriteStatement();

void pCondition();

void pExpr();

void pTerm();

void pFactor();