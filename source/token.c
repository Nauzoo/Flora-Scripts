#include "token.h"
#include <stdio.h>

Token newToken(char* tokenValue, tokenType tokenType){
    Token tokenObj = {tokenValue, tokenType};
    return tokenObj;
}

void printToken(Token token) {
    printf("%s\n", token.tk_value);
}