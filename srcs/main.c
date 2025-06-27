/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:13:48 by datienza          #+#    #+#             */
/*   Updated: 2025/06/27 22:57:49 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_current_pwd = NULL;

static void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->line)
		free(data->line);
	if (data->tokens)
		free_tokens(&data->tokens);
	if (data->processes)
		free_processes(&data->processes);
	if (data->pipes)
		free_pipes(&data->pipes);
}

static int	init_data(t_data *data)
{
	// TODO: Trim string (an all spaces string fail)
	if (ft_strlen(data->line) == 0)
		return (-1);
	data->tokens = tokenize_line(data->line);
	if (!data->tokens)
	{
		print_and_return_error("Error: tokenize_tokens", -1);
	}
	if (validate_syntax(data) != 0)
	{
		print_and_return_error("Error: validate_syntax: Syntax error", -1);
	}
	data->processes = parse_tokens(data->tokens);
	if (!data->processes)
	{
		print_and_return_error("Error: parse_tokens", -1);
	}
	data->processes_count = count_processes(data->processes);
	data->pipes = create_pipes(data->processes_count - 1);
	if (!data->pipes)
	{
		print_and_return_error("Error: parse_tokens", -1);
	}
	assign_pipes_to_processes(data->pipes, data);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*env;
	t_data	data;
	g_current_pwd = getcwd(NULL, 0); //TODO

	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		return (1);
	}
	env = create_env_list(envp);
	ft_memset(&data, 0, sizeof(t_data));
	while (1)
	{
		data.line = readline("$ ");
		if (!data.line)
		{
			free_env_list(&env);
			free(g_current_pwd);
			return (0);
		}
		else if (init_data(&data) == -1)
		{
			free_env_list(&env);
			free_data(&data);
			continue ;
		}
		handle_heredocs(data.processes);
		if (data.processes_count == 1 && (is_builtin(&data.processes->argv[0])))
		{
			save_stdio_fds(data.processes);
			if (apply_redirects(data.processes->redirects))
				continue ;
			exe_builtin(data.processes->argv, env);
			restore_stdio_fds(data.processes);
		}
		else
		{
			execute_pipeline(&data, env);
		}
		free_data(&data);
	}
	free_env_list(&env);
	free(g_current_pwd);//TODO
}
// void sig_handler(int signum)
// {
// 	//nuevo readline
// }

// signal(SIGINT, sig_handler);
// signal(SIGQUIT, SIG_IGN);

// oldsig = signal(SIGQUIT, handle_child)
// //tratas el proceso

// return (signal(SIGQUIT, oldsig))
