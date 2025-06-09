/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:01:22 by datienza          #+#    #+#             */
/*   Updated: 2025/06/07 12:06:15 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_builtin(char **cmd, t_env *env_list)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		printf("cd\n");
	else if (ft_strcmp(cmd[0], "env") == 0)
		print_env_list(env_list);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd, &env_list);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd, &env_list);
	return (0);
}
