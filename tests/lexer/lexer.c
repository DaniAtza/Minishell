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

static void	run_test(char *desc, char *input, int expect_succ, char *test_name)
{
	t_token	*tokens;
	int		success;

	tokens = tokenize_line(input);
	success = tokens != NULL;
	printf("Input: " GRAY "\" " RESET "%s" GRAY " \" %s\n" RESET, input, desc);
	printf("Tokens: ");
	if (tokens)
	{
		print_tokens(tokens);
		free_tokens(&tokens);
	}
	else
		printf(GRAY "(error)" RESET);
	printf("\n" RESET);
	if (success == expect_succ)
		printf(GREEN "OK (Expected: %d, Got: %d)\n" RESET,
			expect_succ, success);
	else
	{
		printf(RED "KO (Expected: %d, Got: %d)" RESET "\n",
			expect_succ, success);
		printf("Test name: %s\n\n", test_name);
	}
	printf("\n");
}

static void	test_empty_input(void)
{
	char	*description;
	char	*input;

	description = "Empty input";
	input = "";
	run_test(description, input, 0, "test_empty_input");
}

static void	test_single_word(void)
{
	char	*description;
	char	*input;

	description = "Single word";
	input = "echo";
	run_test(description, input, 1, "test_single_word");
}

static void	test_multiple_words(void)
{
	char	*description;
	char	*input;

	description = "Multiple words";
	input = "echo hello world";
	run_test(description, input, 1, "test_multiple_words");
}

static void	test_quoted_words(void)
{
	char	*description;
	char	*input;

	description = "Quoted words";
	input = "echo \"hello world\" 'foo bar'";
	run_test(description, input, 1, "test_quoted_words");
}

static void	test_operators(void)
{
	char	*description;
	char	*input;

	description = "Operators";
	input = "echo hello >out <in | grep foo >>append >out2";
	run_test(description, input, 1, "test_operators");
}

static void	test_redirects(void)
{
	char	*description;
	char	*input;

	description = "Redirect operators";
	input = "cat <<EOF >file";
	run_test(description, input, 1, "test_redirects");
}

static void	test_unmatched_quotes(void)
{
	char	*description;
	char	*input;

	description = "Unmatched quotes";
	input = "echo \"hello";
	run_test(description, input, 0, "test_unmatched_quotes");
}

static void	test_comments(void)
{
	char	*description;
	char	*input;

	description = "Comments";
	input = "echo hello # this is a comment";
	run_test(description, input, 1, "test_comments");
}

static void	test_mixed_operators(void)
{
	char	*description;
	char	*input;

	description = "Mixed operators and words";
	input = "ls -la | grep .c > sources.txt | echo done";
	run_test(description, input, 1, "test_mixed_operators");
}

int	main(void)
{
	printf(CYAN "=== Lexer Tests ===\n\n" RESET);
	test_empty_input();
	test_single_word();
	test_multiple_words();
	test_quoted_words();
	test_operators();
	test_redirects();
	test_unmatched_quotes();
	test_comments();
	test_mixed_operators();
	printf(CYAN "=== Tests completed ===\n" RESET);
	return (0);
}
