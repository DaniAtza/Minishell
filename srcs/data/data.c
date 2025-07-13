/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:32:30 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/13 15:55:19 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char *envp[])
{
	ft_memset(data, 0, sizeof(t_data));
	data->env_list = create_env_list(envp); // TODO: Handle error
	data->current_pwd = getcwd(NULL, 0); // TODO: Handle error
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->env_list)
		free_env_list(&data->env_list);
	if (data->current_pwd)
		free(data->current_pwd);
}

int	init_pipeline(t_pipeline *pipeline)
{
	if (ft_strlen(pipeline->line) == 0)
		return (-1);
	pipeline->tokens = tokenize_line(pipeline->line);
	if (!pipeline->tokens)
		return (-1);
	if (validate_syntax(pipeline) != 0)
		return (print_and_return_error("Error: Syntax error", -1));
	pipeline->processes = parse_tokens(pipeline->tokens);
	if (!pipeline->processes)
		return (print_and_return_error("Error: parse_tokens", -1));
	pipeline->process_count = count_processes(pipeline->processes);
	pipeline->pipes = create_pipes(pipeline->process_count - 1);
	if (!pipeline->pipes)
		return (print_and_return_error("Error: create_pipes", -1));
	assign_pipes_to_processes(pipeline->pipes, pipeline);
	return (0);
}

void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	if (pipeline->line)
		free(pipeline->line);
	if (pipeline->tokens)
		free_tokens(&pipeline->tokens);
	if (pipeline->processes)
		free_processes(&pipeline->processes);
	if (pipeline->pipes)
		free_pipes(&pipeline->pipes);
}
