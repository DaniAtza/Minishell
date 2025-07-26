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
	$(addprefix signals/, signals.c signals_handler.c setup_signals.c) \
	$(addprefix env/, env_list.c env_node.c env_utils.c) \
	$(addprefix core/, data.c pipeline.c exit.c) \
	$(addprefix tokenize/, tokens.c tokenize.c tokenize_utils.c) \
	$(addprefix parse/, validate.c processes.c redirects.c argv.c parse.c \
	parse_utils.c) \
	$(addprefix pipes/, pipes.c) \
<<<<<<< HEAD
	$(addprefix builtin/, ft_echo.c ft_cd.c ft_pwd.c ft_export_unset ft_exit.c \
=======
	$(addprefix builtin/, ft_echo.c ft_cd.c ft_pwd.c ft_export_unset.c \
>>>>>>> 262ac74 (refactor: Update ft_cd.c and remove utils_cd.c)
	is_exe_builtin.c) \
	$(addprefix execute/, cmd_search.c execution.c pipes_and_redirects.c \
	utils_exe.c heredoc_temp.c heredoc_exec.c)
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
	mkdir -p $@/signals
	mkdir -p $@/env
	mkdir -p $@/core
	mkdir -p $@/tokenize
	mkdir -p $@/parse
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
