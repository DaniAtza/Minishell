#!/bin/bash

CFLAGS="-Wall -Werror -Wextra -Ilibft/includes -Iincludes -Llibft"
SRCS="srcs/parser/*.c tests/parser/parser.c -lft"
OUTFILE="tests/parser/parser"

# Compile
make
clear
cc $CFLAGS $SRCS -o $OUTFILE

# Run
./$OUTFILE

# Clean
rm $OUTFILE
