.PHONY: all ceems cinco clean

CC = gcc # clang
STD = gnu99
INC = include
SRC = src
BIN = bin
CFLAGS = -std=$(STD) -I./$(INC) -I./$(SRC) -Wall -Wextra -Wfatal-errors -pedantic
COMMON = $(SRC)/tools_declarations.c $(SRC)/tools_utilities.c

all: ceems cinco cinex chime

ceems:
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) $(COMMON) $(SRC)/tools_tokenization.c $(SRC)/ceems.c -o $(BIN)/ceems

cinco:
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) $(COMMON) $(SRC)/cinco.c -o $(BIN)/cinco

cinex:
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) $(SRC)/cinex.c -o $(BIN)/cinex

chime:
	@mkdir -p $(BIN)
	@$(CC) $(CFLAGS) $(COMMON) $(SRC)/chime.c -o $(BIN)/chime

clean:
	@rm -f $(BIN)/*

