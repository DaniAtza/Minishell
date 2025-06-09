LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAGS := -MMD -Wall -Wextra -Werror -I$(LIBFT_DIR)/includes -Iincludes

LDFLAGS := -Llibft
LDLIBS := -lft -lreadline

RM := rm -f
RMDIR := rm -rf

NAME := minishell
SRCS_DIR := srcs
SRCS := main.c \
	$(addprefix lexer/, tokens.c lexer.c utils.c) \
	$(addprefix parser/, process.c redirect.c args.c parser.c \
	validation.c utils.c) \
	$(addprefix env/, env_list.c env_node.c) \
	$(addprefix pipes/, pipes.c) \
	$(addprefix builtin/, is_builtin.c exe_builtin.c ft_pwd.c ft_echo.c ft_export.c) \
	$(addprefix execute/, cmd_search.c execution.c heredoc.c utils_exe.c)
BUILD_DIR := build
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:%.c=$(BUILD_DIR)/%.d)


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(BUILD_DIR)/%.d Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $@
	mkdir -p $@/lexer
	mkdir -p $@/parser
	mkdir -p $@/env
	mkdir -p $@/pipes
	mkdir -p $@/builtin
	mkdir -p $@/execute


%.d: ;

-include $(DEPS)


$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


clean:
	$(RMDIR) $(BUILD_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)


fclean: clean
	$(RM) $(NAME) $(LIBFT)

re:	fclean all
