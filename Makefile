LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAGS := -MMD -Wall -Wextra -Werror -I$(LIBFT_DIR)/includes -Iincludes

LDFLAGS := -Llibft
LDLIBS := -lft -lreadline

RM := rm -f
RMDIR := rm -rf

SRCS_LIBFT = $(addprefix libft/srcs/, ft_isupper.c ft_islower.c ft_isalpha.c \
	ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c \
	ft_strlen.c ft_strnlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strspn.c ft_strcspn.c ft_strcmp.c ft_strncmp.c ft_memchr.c \
	ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_strtok.c ft_itoa.c ft_uitoa.c \
	ft_uitoa_caps.c ft_ultoa.c ft_strmapi.c ft_striteri.c ft_putchar.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putstr.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c \
	ft_atoll.c $(addprefix printf/, ft_printf.c spec_parser.c ft_print_c.c \
	ft_print_s.c ft_print_p.c ft_print_d.c ft_print_u.c ft_print_x.c utils.c))

NAME := minishell
SRCS_DIR := srcs
SRCS := main.c \
	$(addprefix signals/, signals.c signals_handler.c setup_signals.c) \
	$(addprefix env/, env_list.c env_node.c env_utils.c env_to_array.c \
	env_min.c) \
	$(addprefix core/, data.c pipeline.c exit.c) \
	$(addprefix tokenize/, tokens.c tokenize.c tokenize_utils.c) \
	$(addprefix parse/, validate.c processes.c redirects.c argv.c parse.c \
	parse_utils.c) \
	$(addprefix expand/, segments.c segments_identify.c segments_concat.c \
	expand.c expand_words_argv.c expand_words_redirects.c \
	expand_words_heredocs.c expand_parameters.c expand_utils.c) \
	$(addprefix pipes/, pipes.c) \
	$(addprefix builtin/, ft_echo.c ft_pwd.c ft_export_unset.c \
	ft_exit.c is_exe_builtin.c ft_cd.c ft_cd_update.c) \
	$(addprefix execute/, cmd_search.c execution.c pipes_and_redirects.c \
	utils_exe.c heredoc_temp.c heredoc_exec.c)
BUILD_DIR := build
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:%.c=$(BUILD_DIR)/%.d)

SRCS_LIBFT = $(addprefix libft/srcs/, ft_isupper.c ft_islower.c ft_isalpha.c \
	ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isspace.c \
	ft_strlen.c ft_strnlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strspn.c ft_strcspn.c ft_strcmp.c ft_strncmp.c ft_memchr.c \
	ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_strtok.c ft_itoa.c ft_uitoa.c \
	ft_uitoa_caps.c ft_ultoa.c ft_strmapi.c ft_striteri.c ft_putchar.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putstr.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c \
	ft_atoll.c $(addprefix printf/, ft_printf.c spec_parser.c ft_print_c.c \
	ft_print_s.c ft_print_p.c ft_print_d.c ft_print_u.c ft_print_x.c utils.c))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@ -g

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< -g

$(BUILD_DIR):
	mkdir -p $@
	mkdir -p $@/signals
	mkdir -p $@/env
	mkdir -p $@/core
	mkdir -p $@/tokenize
	mkdir -p $@/parse
	mkdir -p $@/expand
	mkdir -p $@/pipes
	mkdir -p $@/builtin
	mkdir -p $@/execute

%.d: ;

-include $(DEPS)


$(LIBFT): $(SRCS_LIBFT)
	$(MAKE) -C $(LIBFT_DIR)


clean:
	$(RMDIR) $(BUILD_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)


fclean: clean
	$(RM) $(NAME) $(LIBFT)

re:	fclean all
