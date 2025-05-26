#include "token.h"
#include <stdio.h>

Token newToken(char* tokenValue, enum tokenTypes tokenType){
    Token tokenObj = {tokenValue, tokenType};
    return tokenObj;
}

void printToken(Token token) {
    printf("%s\n", token.tk_value);
}