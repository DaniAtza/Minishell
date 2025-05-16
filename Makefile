CC := cc
CFLAGS := -MMD -Wall -Wextra -Werror

RM := rm -f
RMDIR := rm -rf

NAME := minishell
SRCS_DIR := srcs
SRCS := main.c
BUILD_DIR := build
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:%.c=$(BUILD_DIR)/%.d)


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(BUILD_DIR)/%.d Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $@


%.d: ;

-include $(DEPS)


clean:
	$(RMDIR) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
