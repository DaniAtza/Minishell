/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:32:30 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/04 22:19:30 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_gdata(t_gdata *gdata, char *envp[])
{
	ft_memset(gdata, 0, sizeof(t_gdata));
	gdata->env_list = create_env_list(envp); // TODO: Handle error
	gdata->current_pwd = getcwd(NULL, 0); // TODO: Handle error
}

int	init_data(t_data *data)
{
	// TODO: Trim string (an all spaces string fail)
	if (ft_strlen(data->line) == 0)
		return (-1);
	data->tokens = tokenize_line(data->line);
	if (!data->tokens)
		print_and_return_error("Error: tokenize_tokens", -1);
	if (validate_syntax(data) != 0)
		print_and_return_error("Error: validate_syntax: Syntax error", -1);
	data->processes = parse_tokens(data->tokens);
	if (!data->processes)
		print_and_return_error("Error: parse_tokens", -1);
	data->processes_count = count_processes(data->processes);
	data->pipes = create_pipes(data->processes_count - 1);
	if (!data->pipes)
		print_and_return_error("Error: parse_tokens", -1);
	assign_pipes_to_processes(data->pipes, data);
	return (0);
}

void	free_gdata(t_gdata *gdata)
{
	if (!gdata)
		return ;
	if (gdata->env_list)
		free_env_list(&gdata->env_list);
	if (gdata->current_pwd)
		free(gdata->current_pwd);
}

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
