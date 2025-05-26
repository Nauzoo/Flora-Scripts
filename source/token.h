#ifndef TOKEN_H
#define TOKEN_H

enum tokenTypes{
    TOKEN_KEY_WORD,
    TOKEN_PLUS_OP,
    TOKEN_MINUS_OP,
    TOKEN_TIMES_OP,
    TOKEN_DIVISION_OP,
    TOKEN_EQUALS_OP,
    TOKEN_DIFFERENT_OP,
    TOKEN_GREATER_OP,
    TOKEN_SMALLER_OP,
    TOKEN_GREATER_OR_EQ_OP,
    TOKEN_SMALLER_OR_EQ_OP,
    TOKEN_NOT_OP,
    TOKEN_INCREMENT_OP,
    TOKEN_DECREMENT_OP,
    TOKEN_ATRIBUITION_OP,
    TOKEN_HASH_OP,
    TOKEN_ARROW_OP,
    TOKEN_DOT_OP,
    TOKEN_ASSIGNMENT,
    TOKEN_COMMA,
    TOKEN_SEMI_COLLON,
    TOKEN_LPAR,
    TOKEN_RPAR,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LCURBRACE,
    TOKEN_RCURBRACE,
    TOKEN_SET_KW,
    TOKEN_STRUCT_KW,
    TOKEN_NUMERIC_KW,
    TOKEN_FUNCTION_KW,
    TOKEN_SELF_REF_KW,
    TOKEN_IF_KW,
    TOKEN_ELSIF_KW,
    TOKEN_ELSE_KW,
    TOKEN_RETURN_KW,
    TOKEN_IDENTIFIER,
    TOKEN_EOF,
    TOKEN_UNKNOWN
};

typedef struct {
    char* tk_value;
    enum tokenTypes tk_type;
} Token;
typedef struct
{
    Token* listpointer;
    int listSize;
} TokenList;


Token newToken(char* tokenValue, enum tokenTypes tokenType);
void printToken(Token token);

#endif
