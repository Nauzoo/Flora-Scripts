#include <stdlib.h>

#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
    char* source;
    size_t sourceSize;
    int position;
    int line;
    int pinPoint;
    int object_size;

} Lexer;

Lexer* newLexer(char* source, size_t sourceSize);

Token getNextToken(Lexer* lexer);
void advancePosition(Lexer* lexer);
void recedePosition(Lexer* Lexer);
Token evaluateTerm(Lexer* Lexer);
Token evaluateSymbol(Lexer* lexer, char symbol);
char peekSource(Lexer* lexer, int offset);
TokenList analiseSource(Lexer* lexer);


#endif
