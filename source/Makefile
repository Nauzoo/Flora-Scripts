
CC = gcc
FLAGS = -Wall -g

all: token lexer callabe clean

callabe:
	$(CC) $(FLAGS) token.o lexer.o florish.c -o flora.exe

lexer:
	$(CC) $(FLAGS) -c lexer.c -o lexer.o

token:
	$(CC) $(FLAGS) -c token.c -o token.o

clean:
	del -f lexer.o
	del -f token.o