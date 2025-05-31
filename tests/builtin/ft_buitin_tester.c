#include "minishell.h"
#include <stdio.h>
#include <string.h>

#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

void	test_is_builtin(char **cmd, char *test_name)
{
	int result;

	printf(CYAN "Test: %s\n" RESET, test_name);
	printf("Input: ");
	if (cmd[0] == NULL)
		printf("NULL");
	else
	{
		for (int i = 0; cmd[i]; i++)
		{
			printf("\"%s\"", cmd[i]);
			if (cmd[i + 1])
				printf(", ");
		}
	}
	printf("\n");

	result = is_builtin(cmd);
	printf("is_builtin result: %d ", result);
	
	if (result == 1)
		printf(GREEN "(builtin detected)" RESET);
	else if (result == 0)
		printf(RED "(not a builtin)" RESET);
	else
		printf(YELLOW "(unexpected return value)" RESET);
	
	printf("\n\n");
}

int	main(void)
{
	printf(CYAN "=== is_builtin Tests ===\n\n" RESET);
	printf("Note: is_builtin checks if first argument is 'echo'\n\n");

	// Test cases para is_builtin - detectar solo "echo"
	char *builtin1[] = {"echo", "hello", NULL};
	test_is_builtin(builtin1, "echo command with arguments");

	char *builtin2[] = {"echo", NULL};
	test_is_builtin(builtin2, "echo command without arguments");

	char *builtin3[] = {"ECHO", "hello", NULL};
	test_is_builtin(builtin3, "ECHO uppercase");

	char *builtin4[] = {"Echo", "hello", NULL};
	test_is_builtin(builtin4, "Echo with capital E");

	char *builtin5[] = {"ls", "-la", NULL};
	test_is_builtin(builtin5, "ls command (should be 0)");

	char *builtin6[] = {"cat", "file.txt", NULL};
	test_is_builtin(builtin6, "cat command (should be 0)");

	char *builtin7[] = {"pwd", NULL};
	test_is_builtin(builtin7, "pwd command (should be 0)");

	char *builtin8[] = {"cd", "directory", NULL};
	test_is_builtin(builtin8, "cd command (should be 0)");

	char *builtin9[] = {NULL};
	test_is_builtin(builtin9, "NULL command array");

	char *builtin10[] = {"", NULL};
	test_is_builtin(builtin10, "Empty string command");

	char *builtin11[] = {"echoo", "test", NULL};
	test_is_builtin(builtin11, "echoo (typo - should be 0)");

	char *builtin12[] = {"echo ", "trailing", "space", NULL};
	test_is_builtin(builtin12, "echo with trailing space");

	char *builtin13[] = {" echo", "leading", "space", NULL};
	test_is_builtin(builtin13, "echo with leading space");

	char *builtin14[] = {"/bin/echo", "test", NULL};
	test_is_builtin(builtin14, "echo with full path (should be 0)");

	char *builtin15[] = {"./echo", "test", NULL};
	test_is_builtin(builtin15, "echo with relative path (should be 0)");

	char *builtin16[] = {"notacommand", NULL};
	test_is_builtin(builtin16, "Non-existent command");

	char *builtin17[] = {"echo123", NULL};
	test_is_builtin(builtin17, "echo with numbers (should be 0)");

	char *builtin18[] = {"export", "VAR=value", NULL};
	test_is_builtin(builtin18, "export command (should be 0)");

	char *builtin19[] = {"env", NULL};
	test_is_builtin(builtin19, "env command (should be 0)");

	char *builtin20[] = {"exit", "0", NULL};
	test_is_builtin(builtin20, "exit command (should be 0)");

	printf(CYAN "=== is_builtin Tests Completed ===\n\n" RESET);
	
	return (0);
}