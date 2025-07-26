/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 12:39:42 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:21:08 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipeline(t_pipeline *pipeline)
{
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
