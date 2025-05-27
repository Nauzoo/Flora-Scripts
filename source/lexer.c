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

void recedePosition(Lexer* lexer) {
    if (lexer->position > 0) {
        lexer->position--;
    }
}

char peekSource(Lexer* lexer,int offset){
    if (lexer->position + offset < lexer->sourceSize)
        return lexer->source[lexer->position + offset];
    return '\0';
}

tokenType getTypeFromTable(char* value) {
    if (value == NULL)
        return TOKEN_UNKNOWN; // throw error
    else if (strcmp(value, "struct") == 0)
        return TOKEN_STRUCT_KW;
    else if (strcmp(value, "fn") == 0)
        return TOKEN_FUNCTION_KW;
    else if (strcmp(value, "self") == 0) 
        return TOKEN_SELF_REF_KW;
    else if (strcmp(value, "if") == 0)
        return TOKEN_IF_KW;
    else if (strcmp(value, "elsif") == 0)
        return TOKEN_ELSIF_KW;
    else if (strcmp(value, "else") == 0)
        return TOKEN_ELSE_KW;
    else if (strcmp(value, "return") == 0)
        return TOKEN_RETURN_KW;
    
    return TOKEN_IDENTIFIER;

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
    recedePosition(lexer);
    buff[indexer] = '\0';

    // THIS IS BALLS. Implemet a hashtable NOW!!
    
    tokenType tkType = getTypeFromTable(buff);
    Token tk = newToken(buff, tkType);
    free(buff);

    return tk;

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

