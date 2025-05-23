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
		return;
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

static void print_redirect(t_redirect *redirect)
{
	printf(GRAY "    filename: " RESET "%s\n", redirect->filename);
	printf(GRAY "    flags: " RESET "%#o\n", redirect->flags);
	printf(GRAY "    mode: " RESET "%#o\n", redirect->mode);
	printf(GRAY "    target_fd: " RESET "%d\n", redirect->target_fd);
	printf(GRAY "    is_heredoc: " RESET "%d\n", redirect->is_heredoc);
	printf(GRAY "    heredoc delimiter: " RESET "%s\n", redirect->delimiter);
}

static void print_redirects(t_redirect *redirects)
{
	t_redirect	*current = redirects;
	int			count = 0;
	
	printf(GRAY "  redirects:" RESET "\n");
	if (!current)
	{
		printf("  %p\n", redirects);
		return;
	}
	
	while (current)
	{
		printf("  redirect [%d]:\n", count++);
		print_redirect(current);
		current = current->next;
	}
}

static void print_args(char **args)
{
	int	i;
	
	printf(GRAY "  argv: " RESET);
	if (!args)
	{
		printf("%p", args);
		return;
	}
	printf("{ ");
	printf("%s", args[0]);
	i = 1;
	while (args[i])
	{
		printf(", %s", args[i]);
		i++;
	}
	printf(" }\n");
}

static void print_process(t_process *process, int index)
{
	printf("process [%d]:\n", index);
	printf(GRAY "  pathname:" RESET " %s\n", process->pathname);
	print_args(process->argv);
	print_redirects(process->redirects);
}

static void print_processes(t_process *processes)
{
	t_process	*current = processes;
	int			index = 0;
	
	if (!current)
	{
		printf("%p\n", processes);
		return;
	}
	
	while (current)
	{
		print_process(current, index++);
		current = current->next;
	}
}

static void run_test(char *desc, char *line, t_token *tokens)
{
	t_process	*processes;
	
	printf(CYAN "%s\n" RESET, desc);
	printf(GRAY "Line: " RESET "%s\n", line);
	printf(GRAY "Tokens: " RESET);
	print_tokens(tokens);
	printf("\n");
	
	processes = parse_tokens(tokens);
	
	printf(GRAY "Results:" RESET "\n");
	print_processes(processes);
	
	if (processes)
		free_processes(&processes);
	printf("\n");
}

static void test_single_command(void)
{
	t_token tk1 = {.type = WORD, .value = "ls", .next = NULL};
	
	run_test("Single command", "ls", &tk1);
}

static void test_two_commands_pipe(void)
{
	t_token tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "grep", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	
	run_test("Two commands with pipe", "ls | grep", &tk1);
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
	
	run_test("Three commands with two pipes", "ls | grep | wc", &tk1);
}

static void test_command_with_redirection(void)
{
	t_token tk1 = {.type = WORD, .value = "echo", .next = NULL};
	t_token tk2 = {.type = GREAT, .value = ">", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "file.txt", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	
	run_test("Command with redirection", "echo > file.txt", &tk1);
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
	
	run_test("Complex command with pipe and redirections", 
		"cat < input.txt | grep > output.txt", &tk1);
}

static void test_empty_input(void)
{
	run_test("Empty input", "", NULL);
}

static void test_input_redirection(void)
{
	t_token tk1 = {.type = WORD, .value = "cat", .next = NULL};
	t_token tk2 = {.type = LESS, .value = "<", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "input.txt", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	
	run_test("Input Redirection", "cat < input.txt", &tk1);
}

static void test_output_redirection(void)
{
	t_token tk1 = {.type = WORD, .value = "echo", .next = NULL};
	t_token tk2 = {.type = WORD, .value = "hello", .next = NULL};
	t_token tk3 = {.type = GREAT, .value = ">", .next = NULL};
	t_token tk4 = {.type = WORD, .value = "output.txt", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	
	run_test("Output Redirection", "echo hello > output.txt", &tk1);
}

static void test_append_redirection(void)
{
	t_token tk1 = {.type = WORD, .value = "echo", .next = NULL};
	t_token tk2 = {.type = WORD, .value = "hello", .next = NULL};
	t_token tk3 = {.type = DGREAT, .value = ">>", .next = NULL};
	t_token tk4 = {.type = WORD, .value = "output.txt", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	
	run_test("Append Redirection", "echo hello >> output.txt", &tk1);
}

static void test_here_document(void)
{
	t_token tk1 = {.type = WORD, .value = "cat", .next = NULL};
	t_token tk2 = {.type = DLESS, .value = "<<", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "EOF", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	
	run_test("Here Document", "cat << EOF", &tk1);
}

static void test_multiple_redirections(void)
{
	t_token tk1 = {.type = WORD, .value = "cat", .next = NULL};
	t_token tk2 = {.type = LESS, .value = "<", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "input.txt", .next = NULL};
	t_token tk4 = {.type = GREAT, .value = ">", .next = NULL};
	t_token tk5 = {.type = WORD, .value = "output.txt", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	
	run_test("Multiple Redirections", "cat < input.txt > output.txt", &tk1);
}

static void test_pipeline_with_redirections(void)
{
	t_token tk1 = {.type = WORD, .value = "cat", .next = NULL};
	t_token tk2 = {.type = LESS, .value = "<", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "input.txt", .next = NULL};
	t_token tk4 = {.type = VLINE, .value = "|", .next = NULL};
	t_token tk5 = {.type = WORD, .value = "grep", .next = NULL};
	t_token tk6 = {.type = WORD, .value = "pattern", .next = NULL};
	t_token tk7 = {.type = GREAT, .value = ">", .next = NULL};
	t_token tk8 = {.type = WORD, .value = "output.txt", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	tk5.next = &tk6;
	tk6.next = &tk7;
	tk7.next = &tk8;
	
	run_test("Pipeline with Redirections",
		"cat < input.txt | grep pattern > output.txt", &tk1);
}

static void test_same_type_redirections(void)
{
	t_token tk1 = {.type = WORD, .value = "cat", .next = NULL};
	t_token tk2 = {.type = LESS, .value = "<", .next = NULL};
	t_token tk3 = {.type = WORD, .value = "input1.txt", .next = NULL};
	t_token tk4 = {.type = LESS, .value = "<", .next = NULL};
	t_token tk5 = {.type = WORD, .value = "input2.txt", .next = NULL};
	
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	
	run_test("Multiple Same-Type Redirections",
		"cat < input1.txt < input2.txt", &tk1);
}

int main(void)
{
	printf(CYAN "=== Parser Tests ===\n\n" RESET);
	
	test_single_command();
	test_two_commands_pipe();
	test_three_commands_pipes();
	test_command_with_redirection();
	test_complex_command();
	test_empty_input();
	test_input_redirection();
	test_output_redirection();
	test_append_redirection();
	test_here_document();
	test_multiple_redirections();
	test_pipeline_with_redirections();
	test_same_type_redirections();
	
	printf(CYAN "=== Tests Completed ===\n\n" RESET);
	return (0);
}