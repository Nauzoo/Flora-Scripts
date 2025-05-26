#include <stdlib.h>
#include <stdio.h>
//#include <threads.h>
#include "lexer.h"

int main(int argc, char *argv[])
{
    FILE * file;
    if (argc > 1) {

        // test if  the file exists [...]

        file = fopen(argv[1], "r");

        // Checking the size of the fille in bytes
        fseek(file, 0L, SEEK_END);
        int fileSize = ftell(file);
        fseek(file, 0L, SEEK_SET);

        char *content = (char*) calloc(fileSize, sizeof(char)); // keeping a copy of the OG file.

        // copying all the content from the file to a single string
        int i = 0;
        char c;
        while((c = fgetc(file)) != EOF){
            content[i] = c;
            i++;
        }

        Lexer* lexer = newLexer(content, fileSize);
        TokenList tokens = analiseSource(lexer);

        for (int i = 0; i < tokens.listSize; i++)
            printToken(tokens.listpointer[i]);
    }




    //formalize the error messages with it's own struct
    else
        printf("u need to provide a file path.\n");

    return 0;
}
