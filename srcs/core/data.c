/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:32:30 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:21:07 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char *envp[])
{
	ft_memset(data, 0, sizeof(t_data));
	data->env_list = create_env_list(envp); // TODO: Handle error
	data->exe_env = NULL;
	data->current_pwd = getcwd(NULL, 0); // TODO: Handle error
	data->last_exit_status = 0;
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->env_list)
		free_env_list(&data->env_list);
	if (data->env_list)
		free_env_array(data->exe_env);
	if (data->current_pwd)
		free(data->current_pwd);
}
