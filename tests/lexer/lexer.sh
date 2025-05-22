#!/bin/bash

CFLAGS="-Wall -Werror -Wextra -Ilibft/includes -Iincludes -Llibft"
SRCS="srcs/lexer/lexer.c srcs/lexer/tokens.c srcs/lexer/utils.c \
  tests/lexer/lexer.c -lft"
OUTFILE="tests/lexer/lexer"

# Compile
clear
cc $CFLAGS $SRCS -o $OUTFILE

# Run
./$OUTFILE

# Clean
rm $OUTFILE