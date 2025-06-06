
NAME = executor
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Rutas relativas desde tests/execute/
INCLUDES_DIR = ../../includes
LIBFT_DIR = ../../libft
SRCS_DIR = ../../srcs

# Includes  
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_DIR)/includes -I.

# Archivos fuente
SRCS = execute.c \
       $(SRCS_DIR)/lexer/lexer.c \
       $(SRCS_DIR)/lexer/tokens.c \
       $(SRCS_DIR)/lexer/utils.c \
       $(SRCS_DIR)/parser/parser.c \
       $(SRCS_DIR)/parser/args.c \
       $(SRCS_DIR)/parser/redirect.c \
       $(SRCS_DIR)/parser/utils.c \
       $(SRCS_DIR)/parser/validation.c \
       $(SRCS_DIR)/parser/process.c \
       $(SRCS_DIR)/execute/execution.c \
       $(SRCS_DIR)/execute/utils_exe.c \
       $(SRCS_DIR)/execute/cmd_search.c \
       $(SRCS_DIR)/execute/heredoc.c \
       $(SRCS_DIR)/builtin/is_builtin.c \
       $(SRCS_DIR)/builtin/ft_echo.c \
       $(SRCS_DIR)/pipes/pipes.c

# Objetos
OBJS = $(SRCS:.c=.o)

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
