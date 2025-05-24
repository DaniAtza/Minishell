#include "minishell.h"
#include <stdio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define GRAY    "\033[90m"

static void	print_tokens(t_data *data)
{
	t_token	*tmp;

	tmp = data->tokens;
	printf(GRAY "\" " RESET);
	while (tmp)
	{
		printf("%s ", tmp->value);
		tmp = tmp->next;
	}
	printf(GRAY "\"");
}

static void	run_test(const char *description, t_data *data, int expected, const char *test_name)
{
	print_tokens(data);
	printf(" %s\n" RESET, description);
	int	result = validate_syntax(data);
	if (result == expected)
		printf(GREEN "OK (Expected: %d, Got: %d)\n" RESET, expected, result);
	else
	{
		printf(RED "KO (Expected: %d, Got: %d)\n" RESET, expected, result);
		printf("Test name: %s\n", test_name);
	}
	printf("\n");
}

static void	test_empty_input(void)
{
	t_data	data = {0};
	run_test("Empty input", &data, -1, "test_empty_input");
}

static void	test_command_single(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "ls", .next = NULL};
	data.tokens = &tk1;
	run_test("Single command", &data, 0, "test_command_single");
}

static void	test_command_multiple(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "echo", .next = NULL};
	t_token	tk2 = {.type = WORD, .value = "ls", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "grep", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	run_test("Multiple commands", &data, 0, "test_command_multiple");
}

static void	test_pipeline_single(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token	tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "grep", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	run_test("Valid pipeline", &data, 0, "test_pipeline_single");
}

static void test_pipeline_multiple(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token	tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "grep", .next = NULL};
	t_token	tk4 = {.type = WORD, .value = "\"validation\"", .next = NULL};
	t_token	tk5 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk6 = {.type = WORD, .value = "wc", .next = NULL};
	t_token	tk7 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk8 = {.type = WORD, .value = "sort", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	tk5.next = &tk6;
	tk6.next = &tk7;
	tk7.next = &tk8;
	run_test("Multiple pipelines", &data, 0, "test_pipeline_multiple");
}

static void test_pipeline_leading_pipe(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk2 = {.type = WORD, .value = "ls", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	run_test("Leading pipe", &data, -1, "test_pipeline_leading_pipe");
}

static void test_pipeline_trailing_pipe(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token	tk2 = {.type = VLINE, .value = "|", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	run_test("Trailing pipe", &data, -1, "test_pipeline_trailing_pipe");
}

static void	test_pipeline_without_command(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = VLINE, .value = "|", .next = NULL};
	data.tokens = &tk1;
	run_test("Pipeline without command", &data, -1, "test_pipeline_without_command");
}

static void	test_pipeline_consecutive_pipes(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token	tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk3 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk4 = {.type = WORD, .value = "grep", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	run_test("Consecutive pipes", &data, -1, "test_pipeline_consecutive_pipes");
}

static void	test_redirection_output(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "echo", .next = NULL};
	t_token	tk2 = {.type = GREAT, .value = ">", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "file.txt", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	run_test("Valid redirection output", &data, 0, "test_redirection_output");
}

static void	test_redirection_input(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "cat", .next = NULL};
	t_token	tk2 = {.type = LESS, .value = "<", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "file.txt", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	run_test("Valid redirection input", &data, 0, "test_redirection_input");
}

static void	test_redirection_append(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "echo", .next = NULL};
	t_token	tk2 = {.type = DGREAT, .value = ">>", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "file.txt", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	run_test("Valid redirection append", &data, 0, "test_redirection_append");
}

static void	test_redirection_heredoc(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "cat", .next = NULL};
	t_token	tk2 = {.type = DLESS, .value = "<<", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "EOF", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	run_test("Valid redirection heredoc", &data, 0, "test_redirection_heredoc");
}

static void	test_redirection_output_no_file(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "echo", .next = NULL};
	t_token	tk2 = {.type = GREAT, .value = ">", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	run_test("Redirection output without file", &data, -1, "test_redirection_output_no_file");
}

static void	test_redirection_input_no_file(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "cat", .next = NULL};
	t_token	tk2 = {.type = LESS, .value = "<", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	run_test("Redirection input without file", &data, -1, "test_redirection_input_no_file");
}

static void	test_redirection_append_no_file(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "echo", .next = NULL};
	t_token	tk2 = {.type = DGREAT, .value = ">>", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	run_test("Redirection append without file", &data, -1, "test_redirection_append_no_file");
}

static void	test_redirection_heredoc_no_delimiter(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "cat", .next = NULL};
	t_token	tk2 = {.type = DLESS, .value = "<<", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	run_test("Redirection heredoc without delimiter", &data, -1, "test_redirection_heredoc_no_delimiter");
}

static void test_mixed_1_valid(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token	tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "grep", .next = NULL};
	t_token	tk4 = {.type = LESS, .value = "<", .next = NULL};
	t_token	tk5 = {.type = WORD, .value = "file.txt", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	run_test("Mixed 1 valid", &data, 0, "test_mixed_1_valid");
}

static void test_mixed_1_invalid(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token	tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "grep", .next = NULL};
	t_token	tk4 = {.type = LESS, .value = "<", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	run_test("Mixed 1 invalid", &data, -1, "test_mixed_1_invalid");
}
static void test_mixed_2_valid(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token	tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk3 = {.type = DGREAT, .value = ">>", .next = NULL};
	t_token	tk4 = {.type = WORD, .value = "file.txt", .next = NULL};
	t_token	tk5 = {.type = WORD, .value = "grep", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	run_test("Mixed 2 valid", &data, 0, "test_mixed_2_valid");
}

static void test_mixed_2_invalid(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token	tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk3 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk4 = {.type = DGREAT, .value = ">>", .next = NULL};
	t_token	tk5 = {.type = WORD, .value = "file.txt", .next = NULL};
	t_token	tk6 = {.type = WORD, .value = "grep", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	tk5.next = &tk6;
	run_test("Mixed 2 invalid", &data, -1, "test_mixed_2_invalid");
}

static void test_mixed_3_valid(void)
{
	t_data	data = {0};
	t_token	tk1 = {.type = WORD, .value = "ls", .next = NULL};
	t_token	tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "grep", .next = NULL};
	t_token	tk4 = {.type = DLESS, .value = "<<", .next = NULL};
	t_token	tk5 = {.type = WORD, .value = "EOF", .next = NULL};
	data.tokens = &tk1;
	tk1.next = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	run_test("Mixed 3 valid", &data, 0, "test_mixed_3_valid");
}

static void test_mixed_3_invalid(void)
{
	t_data	data = {0};
	t_token	tk2 = {.type = VLINE, .value = "|", .next = NULL};
	t_token	tk3 = {.type = WORD, .value = "grep", .next = NULL};
	t_token	tk4 = {.type = DLESS, .value = "<<", .next = NULL};
	t_token	tk5 = {.type = WORD, .value = "EOF", .next = NULL};
	data.tokens = &tk2;
	tk2.next = &tk3;
	tk3.next = &tk4;
	tk4.next = &tk5;
	run_test("Mixed 3 invalid", &data, -1, "test_mixed_3_invalid");
}

int	main(void)
{
	printf(CYAN "=== Syntax Validation Tests ===\n\n" RESET);
	test_empty_input();
	test_command_single();
	test_command_multiple();
	test_pipeline_single();
	test_pipeline_multiple();
	test_pipeline_leading_pipe();
	test_pipeline_trailing_pipe();
	test_pipeline_without_command();
	test_pipeline_consecutive_pipes();
	test_redirection_output();
	test_redirection_input();
	test_redirection_append();
	test_redirection_heredoc();
	test_redirection_output_no_file();
	test_redirection_input_no_file();
	test_redirection_append_no_file();
	test_redirection_heredoc_no_delimiter();
	test_mixed_1_valid();
	test_mixed_1_invalid();
	test_mixed_2_valid();
	test_mixed_2_invalid();
	test_mixed_3_valid();
	test_mixed_3_invalid();
	printf(CYAN "=== Tests completed ===\n" RESET);
	return (0);
}
