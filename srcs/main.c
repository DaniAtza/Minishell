/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:13:48 by datienza          #+#    #+#             */
/*   Updated: 2025/05/30 17:57:15 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
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

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 1)
	{
		printf("Usage: %s\n", argv[0]);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	while (1)
	{
		data.line = readline("$ ");
		if (!data.line)
			return (0);
		// TODO: Trim string (an all spaces string fail)
		else if (ft_strlen(data.line) == 0) 
		{
			free_data(&data);
			continue;
		}
		data.tokens = tokenize_line(data.line);
		if (!data.tokens)
		{
			printf("Error: tokenize_tokens\n");
			free_data(&data);
			continue;
		}
		if (validate_syntax(&data) != 0)
		{
			printf("Error: validate_syntax: Syntax error\n");
			free_data(&data);
			continue;
		}
		data.processes = parse_tokens(data.tokens);
		if (!data.processes)
		{
			printf("Error: parse_tokens\n");
			free_data(&data);
			continue;
		}
		data.processes_count = count_processes(data.processes);
		data.pipes = create_pipes(data.processes_count - 1);
		assign_pipes_to_processes(data.pipes, &data);
		execute_pipeline(&data);
		free_data(&data);
	}
}
