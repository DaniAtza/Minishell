/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exe_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:01:22 by datienza          #+#    #+#             */
/*   Updated: 2025/07/27 17:58:23 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **argv)
{
	if (!argv || !argv[0])
		return (0);
	if (ft_strcmp(argv[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "env") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (1);
	return (0);
}

int	exe_builtin(char **argv, t_pipeline *pipeline, t_data *data)
{
	if (!argv || !argv[0])
		return (-1);
	if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argv, data);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd(data->current_pwd, data);
	else if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, data));
	else if (ft_strcmp(argv[0], "env") == 0)
		print_env_list(data->env_list, data);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, data->env_list, data));
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argv, data->env_list, data);
	else if (ft_strcmp(argv[0], "exit") == 0)
		ft_exit(argv, pipeline, data);
	return (0);
}
