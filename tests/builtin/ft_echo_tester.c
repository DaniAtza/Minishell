#include "minishell.h"
#include <stdio.h>
#include <string.h>

#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

void	test_ft_echo(char **args, char *test_name)
{
	int result;

	printf(CYAN "Test: %s\n" RESET, test_name);
	printf("Input: ");
	for (int i = 0; args[i]; i++)
	{
		printf("\"%s\"", args[i]);
		if (args[i + 1])
			printf(", ");
	}
	printf("\n");

	printf("ft_echo output: ");
	fflush(stdout);
	result = ft_echo(args);
	printf("\nReturn value: %d\n\n", result);
}

int	main(void)
{
	printf(CYAN "=== ft_echo Tests ===\n\n" RESET);
	printf("Note: ft_echo receives arrays where [0] is always 'echo'\n\n");

	// Test cases para ft_echo - todos empiezan con "echo"
	char *test1[] = {"echo", "Hello", "World", NULL};
	test_ft_echo(test1, "Basic echo with arguments");

	char *test2[] = {"echo", "-n", "Hello", "World", NULL};
	test_ft_echo(test2, "Echo with -n flag");

	char *test3[] = {"echo", NULL};
	test_ft_echo(test3, "Echo without arguments");

	char *test4[] = {"echo", "-n", NULL};
	test_ft_echo(test4, "Echo with only -n flag");

	char *test5[] = {"echo", "", NULL};
	test_ft_echo(test5, "Echo with empty string");

	char *test6[] = {"echo", "-n", "", "test", NULL};
	test_ft_echo(test6, "Echo with -n and empty string");

	char *test7[] = {"echo", "Line1", "Line2", "Line3", NULL};
	test_ft_echo(test7, "Echo with multiple arguments");

	char *test8[] = {"echo", "-n", "-n", "test", NULL};
	test_ft_echo(test8, "Echo with multiple -n flags");

	char *test9[] = {"echo", "Special", "chars:", "!@#$%^&*()", NULL};
	test_ft_echo(test9, "Echo with special characters");

	char *test10[] = {"echo", "-n", "multiple", "words", "here", NULL};
	test_ft_echo(test10, "Echo -n with multiple words");

	char *test11[] = {"echo", "Hello", "-n", "World", NULL};
	test_ft_echo(test11, "Echo with -n in middle (should print -n as text)");

	char *test12[] = {"echo", "-N", "uppercase", "flag", NULL};
	test_ft_echo(test12, "Echo with uppercase -N (should print as text)");

	char *test13[] = {"echo", "--n", "double", "dash", NULL};
	test_ft_echo(test13, "Echo with --n (should print as text)");

	char *test14[] = {"echo", "-", "single", "dash", NULL};
	test_ft_echo(test14, "Echo with single dash");

	char *test15[] = {"echo", "text", "-n", "flag", "after", NULL};
	test_ft_echo(test15, "Echo with -n after other arguments");

	char *test16[] = {"echo", "\t", "tab", "character", NULL};
	test_ft_echo(test16, "Echo with tab character");

	char *test17[] = {"echo", "\"quoted\"", "text", NULL};
	test_ft_echo(test17, "Echo with quoted text");

	char *test18[] = {"echo", "-n", "-n", "-n", "multiple", "flags", NULL};
	test_ft_echo(test18, "Echo with three -n flags");

	char *test19[] = {"echo", "First", "Second", "Third", "Fourth", "Fifth", NULL};
	test_ft_echo(test19, "Echo with many arguments");

	char *test20[] = {"echo", "One", NULL};
	test_ft_echo(test20, "Echo with single argument");

	printf(CYAN "=== ft_echo Tests Completed ===\n\n" RESET);
	
	return (0);
}