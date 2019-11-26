#pragma once
#include "token.h"
#include "error.h"
#include <regex>
#include <functional>
#include <fstream>
#include <iostream>
#include <queue>

extern queue<Token> buffer;

void Lexing(const string filepath);

void Matching(string line);

void TextLexing(const string filepath);