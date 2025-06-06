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
			free(data.line);
			continue;
		}
		data.tokens = tokenize_line(data.line);
		if (!data.tokens)
		{
			printf("Error: tokenize_tokens\n");
			free(data.line);
			continue;
		}
		if (validate_syntax(&data) != 0)
		{
			printf("Error: validate_syntax: Syntax error\n");
			free_tokens(&data.tokens);
			free(data.line);
			continue;
		}
		data.processes = parse_tokens(data.tokens);
		if (!data.processes)
		{
			free_tokens(&data.tokens);
			free(data.line);
			printf("Error: parse_tokens\n");
			continue;
		}
		data.processes_count = count_processes(data.processes);
		data.pipes = create_pipes(data.processes_count - 1);
		assign_pipes_to_processes(data.pipes, &data);
		execute_pipeline(&data);
		free_pipes(&data.pipes);
		free_processes(&data.processes);
		free_tokens(&data.tokens);
		free(data.line);
	}
}
