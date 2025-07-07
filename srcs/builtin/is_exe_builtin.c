/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exe_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:01:22 by datienza          #+#    #+#             */
/*   Updated: 2025/07/07 20:05:49 by dagredan         ###   ########.fr       */
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
	return (0);
}

int	exe_builtin(char **argv, t_gdata *gdata)
{
	if (!argv || !argv[0])
		return (-1);
	if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd(gdata->current_pwd);
	else if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(argv, gdata);
	else if (ft_strcmp(argv[0], "env") == 0)
		print_env_list(gdata->env_list);
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(argv, gdata->env_list);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argv, gdata->env_list);
	return (0);
}
