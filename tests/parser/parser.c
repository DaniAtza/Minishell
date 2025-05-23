#include "minishell.h"
#include <stdio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define GRAY    "\033[90m"

static void	print_tokens(t_token *tokens)
{
	char	*types[6] = {"LESS", "GREAT", "DLESS", "DGREAT", "VLINE", "WORD"};
	t_token	*current;

	if (!tokens)
	{
		printf("(NULL)");
		return ;
	}
	current = tokens;
	printf("%s ", current->value);
	printf(GRAY "(%s)", types[current->type]);
	current = current->next;
	while (current)
	{
		printf(GRAY " -> " RESET);
		printf("%s ", current->value);
		printf(GRAY "(%s)" RESET, types[current->type]);
		current = current->next;
	}
}

static int count_processes(t_process *processes)
{
	int count = 0;
	t_process *current = processes;
	
	while (current)
	{
		count++;
		current = current->next;
	}
	
	return (count);
}

static void run_test(char *desc, int expected, t_token *tokens)
{
	t_process 	*processes;
	int 		count;
	
	printf(GRAY "Test:" RESET " %s\n", desc);
	printf(GRAY "Tokens: " RESET);
	print_tokens(tokens);
	printf("\n");
	
	processes = parse_tokens(tokens);
	count = count_processes(processes);
	
	if (count == expected)
		printf(GREEN "OK (Expected: %d, Got: %d)\n" RESET, expected, count);
	else
		printf(RED "KO (Expected: %d, Got: %d)\n" RESET, expected, count);
	
	if (processes)
		free_processes(&processes);
	printf("\n");
}

static void test_single_command(void)
{
	t_token tk1 = {.type = WORD, .value = "ls", .next = NULL};
	
	run_test("Single command", 1, &tk1);
}

static void test_two_commands_pipe(void)
{
	t_token tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "grep", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	
	run_test("Two commands with pipe", 2, &tk1);
}

static void test_three_commands_pipes(void)
{
	t_token tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "grep", .next = NULL};
	t_token tk4 = {.type = VLINE, .value = "|", .next = NULL};
	t_token tk5 = {.type = WORD, .value = "wc", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	
	run_test("Three commands with two pipes", 3, &tk1);
}

static void test_command_with_redirection(void)
{
	t_token tk1 = {.type = WORD, .value = "echo", .next = NULL};
	t_token tk2 = {.type = GREAT, .value = ">", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "file.txt", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	
	run_test("Command with redirection", 1, &tk1);
}

static void test_complex_command(void)
{
	t_token tk1 = {.type = WORD, .value = "cat", .next = NULL};
	t_token tk2 = {.type = LESS, .value = "<", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "input.txt", .next = NULL};
	t_token tk4 = {.type = VLINE, .value = "|", .next = NULL};
	t_token tk5 = {.type = WORD, .value = "grep", .next = NULL};
	t_token tk6 = {.type = GREAT, .value = ">", .next = NULL};
	t_token tk7 = {.type = WORD, .value = "output.txt", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	tk5.next = &tk6;
	tk6.next = &tk7;
	
	run_test("Complex command with pipe and redirections", 2, &tk1);
}

static void test_empty_input(void)
{
	run_test("Empty (NULL) token list", 0, NULL);
}

int main(void)
{
	printf(CYAN "=== Parser Tests: Count Processes ===\n\n" RESET);
	
	test_single_command();
	test_two_commands_pipe();
	test_three_commands_pipes();
	test_command_with_redirection();
	test_complex_command();
	test_empty_input();
	
	printf(CYAN "=== Parser Tests Completed ===\n\n" RESET);
	return (0);
}