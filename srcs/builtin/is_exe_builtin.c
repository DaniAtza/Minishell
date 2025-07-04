/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exe_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:01:22 by datienza          #+#    #+#             */
/*   Updated: 2025/07/04 22:19:23 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	return (0);
}

int	exe_builtin(char **cmd, t_gdata *gdata)
{
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd(gdata->current_pwd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(cmd, gdata);
	else if (ft_strcmp(cmd[0], "env") == 0)
		print_env_list(gdata->env_list);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd, gdata->env_list);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd, gdata->env_list);
	return (0);
}
