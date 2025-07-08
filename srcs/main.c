/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:13:48 by datienza          #+#    #+#             */
/*   Updated: 2025/07/08 19:06:15 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_minishell_args(int argc, char *argv[])
{
	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		exit(1);
	}
}

int	main_loop(t_pipeline *pipeline, t_data *data)
{
	pipeline->line = readline("$ ");
	if (!pipeline->line)
		return (-1);
	else if (init_pipeline(pipeline) == -1)
		return (0);
	add_history(pipeline->line);
	handle_heredocs(pipeline->processes);
	handle_execution(pipeline, data);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data		data;
	t_pipeline	pipeline;

	check_minishell_args(argc, argv);
	init_data(&data, envp);
	ft_memset(&pipeline, 0, sizeof(t_pipeline));
	while (1)
	{
		if (main_loop(&pipeline, &data) == -1)
			break ;
		free_pipeline(&pipeline);
	}
	rl_clear_history();
	free_data(&data);
	return (0);
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
