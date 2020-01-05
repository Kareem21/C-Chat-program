#Simple makefile for Programming assignment 1 - CS457

#variable declaration :-
cc=gcc      
MAKE=make
RM =rm

#targets .
all: chat.c
	$(cc) -o chat chat.c	
	
clean:chat
	$(RM) chat
