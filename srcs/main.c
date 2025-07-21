/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:13:48 by datienza          #+#    #+#             */
/*   Updated: 2025/07/20 12:38:02 by datienza         ###   ########.fr       */
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
	if (ft_strlen(pipeline->line) == 0)
		return (0);
	add_history(pipeline->line);
	if (init_pipeline(pipeline) == -1)
		return (0);
	if (handle_heredocs(data, pipeline->processes) != 0)
		return (0);
	handle_execution(pipeline, data);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data		data;
	t_pipeline	pipeline;

	setup_signals();
	check_minishell_args(argc, argv);
	init_data(&data, envp);
	ft_memset(&pipeline, 0, sizeof(t_pipeline));
	while (1)
	{
		if (main_loop(&pipeline, &data) == -1)
			break ;
		free_pipeline(&pipeline);
		setup_signals();
	}
	rl_clear_history();
	free_data(&data);
	return (0);
}
