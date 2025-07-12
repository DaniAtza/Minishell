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
	$(addprefix parser/, process.c redirect.c argv.c parser.c \
	validation.c utils.c) \
	$(addprefix data/, data.c) \
	$(addprefix env/, env_list.c env_node.c env_print.c) \
	$(addprefix pipes/, pipes.c) \
	$(addprefix builtin/, is_exe_builtin.c ft_echo.c ft_pwd.c ft_cd.c utils_cd.c ft_export_unset.c) \
	$(addprefix execute/, cmd_search.c execution.c pipes_and_redirects.c heredoc.c utils_exe.c) \
	$(addprefix signals/, signals.c)
BUILD_DIR := build
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:%.c=$(BUILD_DIR)/%.d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@ -g

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(BUILD_DIR)/%.d Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -g

$(BUILD_DIR):
	mkdir -p $@
	mkdir -p $@/lexer
	mkdir -p $@/parser
	mkdir -p $@/data
	mkdir -p $@/env
	mkdir -p $@/pipes
	mkdir -p $@/builtin
	mkdir -p $@/execute
	mkdir -p $@/signals

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
