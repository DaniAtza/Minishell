#!/bin/bash

CFLAGS="-Wall -Werror -Wextra -Ilibft/includes -Iincludes -Llibft"
SRCS="srcs/builtin/ft_echo.c tests/builtin/ft_echo_tester.c -lft"
OUTFILE="tests/builtin/ft_echo_tester"

# Compile
make
clear
cc $CFLAGS $SRCS -o $OUTFILE

# Run
./$OUTFILE

# Clean
rm $OUTFILE