#!/bin/bash

CFLAGS="-Wall -Werror -Wextra -Ilibft/includes -Iincludes -Llibft"
SRCS="srcs/execute/cmd_search.c tests/execute/cmd_search.c -lft"
OUTFILE="tests/execute/cmd_search"

# Compile
make
clear
cc $CFLAGS $SRCS -o $OUTFILE

# Run
./$OUTFILE

# Clean
rm $OUTFILE
