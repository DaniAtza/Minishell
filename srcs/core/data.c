/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:32:30 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/05 12:40:14 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char *envp[])
{
	char	**env_min;

	ft_memset(data, 0, sizeof(t_data));
	if (!envp || !envp[0])
	{
		env_min = create_minimal_env();
		if (!env_min)
			perror_exit("init_data: create_minimal_env", 1);
		data->env_list = create_env_list(env_min);
	}
	else
		data->env_list = create_env_list(envp);
	if (!data->env_list)
		perror_exit("init_data: create_env_list", 1);
	data->exe_env = NULL;
	data->current_pwd = getcwd(NULL, 0);
	if (!data->current_pwd)
	{
		free_env_list(&data->env_list);
		perror_exit("init_data: getcwd", 1);
	}
	data->last_exit_status = 0;
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->env_list)
		free_env_list(&data->env_list);
	if (data->exe_env)
		free_env_array(data->exe_env);
	if (data->current_pwd)
		free(data->current_pwd);
}
