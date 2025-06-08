#include "minishell.h"

#define RESET   "\033[0m"
#define CYAN    "\033[36m"

void print_command(char *command)
{
	printf("\n" CYAN "command: %s" RESET "\n", command);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env;

	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		return (1);
	}
	env = create_env_list(envp);

	print_command("env");
	print_env_list(env);

	print_command("export NAME=test; env");
	update_env_node("NAME=test", &env);
	print_env_list(env);

	print_command("unset NAME; env");
	delete_env_node("NAME", &env);
	print_env_list(env);

	print_command("export SHELL=/bin/sh; env");
	update_env_node("SHELL=/bin/sh", &env);
	print_env_list(env);

	print_command("unset SHELL; env");
	delete_env_node("SHELL", &env);
	print_env_list(env);

	print_command("export MINISHELL_AUTHORS=dani_and_david; env");
	update_env_node("MINISHELL_AUTHORS=dani_and_david", &env);
	print_env_list(env);
}