#!/bin/bash

CFLAGS="-Wall -Werror -Wextra -Ilibft/includes -Iincludes"
SRCS="srcs/parser/validation.c tests/parser/validation.c"
OUTFILE="tests/parser/validation"

# Compile
clear
cc $CFLAGS $SRCS -o $OUTFILE

# Run
./$OUTFILE

# Clean
rm $OUTFILE
