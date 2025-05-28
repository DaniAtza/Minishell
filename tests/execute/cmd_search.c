#include "minishell.h"
#include <stdio.h>

#define RESET   "\033[0m"
#define CYAN    "\033[36m"

void	run_test(char *cmd_name)
{
	char	*pathname;
	pid_t	pid;

	printf(CYAN "Command name: %s\n" RESET, cmd_name);

	pathname = get_pathname(cmd_name);
	printf("get_pathname:  %s\n", pathname);

	ft_putstr("which command: ");
	pid = fork();
	if (pid == 0)
	{
		execlp("which", "which", cmd_name, NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	free(pathname);
	printf("\n\n");
}

int	main(void)
{
	printf(CYAN "=== Path Search Tests ===\n\n" RESET);

	run_test("ls");
	run_test("cat");
	run_test("grep");
	run_test("wc");
	run_test("");
	run_test("nonexistent_command");
	run_test("/bin/ls");
	run_test("/usr/bin/grep");

	printf(CYAN "=== Tests Completed ===\n\n" RESET);
}