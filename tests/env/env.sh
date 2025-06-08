#!/bin/bash

CFLAGS="-Wall -Werror -Wextra -Ilibft/includes -Iincludes -Llibft"
SRCS="srcs/env/env_list.c srcs/env/env_node.c tests/env/env.c -lft"
OUTFILE="tests/env/env"

# Compile
make
clear
cc $CFLAGS $SRCS -o $OUTFILE

# Run
./$OUTFILE

# Clean
rm $OUTFILE