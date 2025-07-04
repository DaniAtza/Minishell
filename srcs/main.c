/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:13:48 by datienza          #+#    #+#             */
/*   Updated: 2025/07/04 22:20:02 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void check_args(int argc, char *argv[])
{
	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		exit(1);
	}
}

int	main_loop(t_data *data, t_gdata *gdata)
{
	data->line = readline("$ ");
	if (!data->line)
		return (-1);
	else if (init_data(data) == -1)
		return (0);
	add_history(data->line);
	handle_heredocs(data->processes);
	handle_execution(data, gdata);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	t_gdata	gdata;

	check_args(argc, argv);
	init_gdata(&gdata, envp);
	ft_memset(&data, 0, sizeof(t_data));
	while (1)
	{
		if (main_loop(&data, &gdata) == -1)
			break ;
		free_data(&data);
	}
	rl_clear_history();
	free_gdata(&gdata);
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
