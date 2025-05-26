#include "lexer.h"
#include "token.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <wchar.h>


Lexer* newLexer(char* source, size_t sourceSize) {
    Lexer* lexerObj = malloc(sizeof(Lexer));
    
    lexerObj->source = source;
    lexerObj->line = 1;
    lexerObj->position = 0;
    lexerObj->pinPoint = 0;
    lexerObj->sourceSize = sourceSize;
    lexerObj->object_size = 0;
    return lexerObj;
}

void advancePosition(Lexer* lexer) {

    if (lexer->position < lexer->sourceSize && lexer->source[lexer->position] != '\0') {
        lexer->position++;
    }

}

char peekSource(Lexer* lexer,int offset){
    if (lexer->position + offset < lexer->sourceSize)
        return lexer->source[lexer->position + offset];
    return '\0';
}

Token evaluateTerm(Lexer* lexer){

    int indexer = 0;
    char* buff = malloc(sizeof(char));
    do {
        buff[indexer] = lexer->source[lexer->position];
        indexer++;
        buff = (char*) realloc(buff, sizeof(char)*indexer);
        advancePosition(lexer);

    } while (iswalnum(lexer->source[lexer->position]) || lexer->source[lexer->position] == '_');
    lexer->position--;
    // THIS IS BALLS. Implemet a hashtable NOW!!
    if (strcmp(buff, "set") == 0){
        free(buff);
        return newToken("set", TOKEN_SET_KW);
    }
    else if (strcmp(buff, "struct") == 0) {
        free(buff);
        return newToken("struct", TOKEN_STRUCT_KW);
    }
    else if (strcmp(buff, "numeric") == 0) {
        free(buff);
        return newToken("numeric", TOKEN_NUMERIC_KW);
    }
    else if (strcmp(buff, "fn") == 0){
        free(buff);
        return newToken("fn", TOKEN_FUNCTION_KW);
    }
    else if (strcmp(buff, "self") == 0) {
        free(buff);
        return newToken("self", TOKEN_SELF_REF_KW);
    }
    else if (strcmp(buff, "if") == 0) {
        free(buff);
        return newToken("if", TOKEN_IF_KW);
    }
    else if (strcmp(buff, "elsif") == 0) {
        free(buff);
        return newToken("elsif", TOKEN_ELSIF_KW);
    }
    else if (strcmp(buff, "else") == 0) {
        free(buff);
        return newToken("else", TOKEN_ELSE_KW);
    }
    else if (strcmp(buff, "return") == 0) {
        free(buff);
        return newToken("return", TOKEN_RETURN_KW);
    }
    else{
        free(buff);
        return newToken(buff, TOKEN_IDENTIFIER);
    } 

}
Token evaluateSymbol(Lexer* lexer, char symbol){

    switch (symbol) {
    case '+':
        if (peekSource(lexer, 1) == '+') { advancePosition(lexer); return newToken("++", TOKEN_INCREMENT_OP); }
        else if (peekSource(lexer, 1) == '=') { advancePosition(lexer); return newToken("+=", TOKEN_INCREMENT_OP); }
        else return newToken("+", TOKEN_PLUS_OP);

    case '-':
        if (peekSource(lexer, 1) == '-') { advancePosition(lexer); return newToken("--", TOKEN_DECREMENT_OP); }
        else if (peekSource(lexer, 1) == '=') { advancePosition(lexer); return newToken("-=", TOKEN_DECREMENT_OP); }
        else if (peekSource(lexer, 1) == '>') { advancePosition(lexer); return newToken("->", TOKEN_ARROW_OP); }
        else return newToken("-", TOKEN_PLUS_OP);

    case '=':
        if (peekSource(lexer, 1) == '=') { advancePosition(lexer); return newToken("==", TOKEN_EQUALS_OP); }
        else return newToken("=", TOKEN_ASSIGNMENT);

    case '!':
        if (peekSource(lexer, 1) == '=') { advancePosition(lexer); return newToken("!=", TOKEN_DIFFERENT_OP); }
        else return newToken("!", TOKEN_NOT_OP);

    case '>':
        if (peekSource(lexer, 1) == '=') { advancePosition(lexer); return newToken(">=", TOKEN_GREATER_OR_EQ_OP); }
        else return newToken(">", TOKEN_GREATER_OP);

    case '<':
        if (peekSource(lexer, 1) == '=') { advancePosition(lexer); return newToken("<=", TOKEN_SMALLER_OR_EQ_OP); }
        else return newToken("<", TOKEN_SMALLER_OP);
    
    case '*':
        return newToken("*", TOKEN_TIMES_OP);
    case '/':
        return newToken("/", TOKEN_DIVISION_OP);
    case ':':
        return newToken(":", TOKEN_ATRIBUITION_OP);
    case '#':
        return newToken("#", TOKEN_HASH_OP);
    case '.':
        return newToken(".", TOKEN_DOT_OP);
    case ',':
        return newToken(",", TOKEN_COMMA);
    case ';':
        return newToken(";", TOKEN_SEMI_COLLON);
    case '(':
        return newToken("(", TOKEN_LPAR);
    case ')':
        return newToken(")", TOKEN_RPAR);
    case '[':
        return newToken("[", TOKEN_LBRACE);
    case ']':
        return newToken("]", TOKEN_RBRACE);
    case '{':
        return newToken("{", TOKEN_LCURBRACE);
    case '}':
        return newToken("}", TOKEN_RCURBRACE);
    case '\0':
        return newToken("end_of_file", TOKEN_EOF);
    default:
        return newToken("", TOKEN_UNKNOWN);
    }
}

Token getNextToken(Lexer* lexer){
    
    char currentChar;
    do {
        advancePosition(lexer);
        currentChar = lexer->source[lexer->position];
        if (currentChar == '\n')
            lexer->line++;
    } while (iswspace(currentChar));
    
    if (iswalpha(currentChar)) 
        return evaluateTerm(lexer);
    else
        return evaluateSymbol(lexer, currentChar);
    
}

TokenList analiseSource(Lexer* lexer){
    
    int listIndexer = 0;
    Token* tokenList = (Token*) malloc(sizeof(Token));

    Token lastToken;
    do
    {  
        lastToken = getNextToken(lexer);
        tokenList[listIndexer] = lastToken;
        tokenList = (Token*) realloc(tokenList, (sizeof(Token) * (listIndexer + 2)));
        listIndexer++;
    } while ((lastToken.tk_type != TOKEN_EOF));

    TokenList list = {tokenList, listIndexer};
    return list;    
}

