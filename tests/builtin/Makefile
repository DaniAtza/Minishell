# Makefile for exit tester

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = ft_exit_tester

# Source files
SRCS = ft_exit_tester.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(NAME)

# Build the tester
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

# Test targets
test: $(NAME)
	@echo "Running C tester..."
	@cd ../.. && ./tests/builtin/$(NAME)

test_sh:
	@echo "Running shell script tester..."
	@cd ../.. && bash ./tests/builtin/test_exit.sh

test_both: test test_sh

# Quick test (just compile and run)
quick: re test

# Install (copy files to tests/builtin directory)
install:
	@echo "Files should be placed in tests/builtin/ directory"
	@echo "Current files:"
	@echo "- ft_exit_tester.c"
	@echo "- test_exit.sh" 
	@echo "- Makefile"

# Help
help:
	@echo "Available targets:"
	@echo "  all        - Build the tester"
	@echo "  test       - Run C tester"
	@echo "  test_sh    - Run shell script tester"
	@echo "  test_both  - Run both testers"
	@echo "  quick      - Rebuild and test"
	@echo "  clean      - Remove object files"
	@echo "  fclean     - Remove all generated files"
	@echo "  re         - Rebuild"
	@echo "  help       - Show this help"

.PHONY: all clean fclean re test test_sh test_both quick install help
