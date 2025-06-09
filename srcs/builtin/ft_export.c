/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:47:18 by datienza          #+#    #+#             */
/*   Updated: 2025/06/09 16:56:36 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **cmd, t_env **env_list)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		update_env_node(cmd[i], env_list);
		i++;
	}
	return (0);
}

int	ft_unset(char **cmd, t_env **env_list)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		delete_env_node(cmd[i], env_list);
		i++;
	}
	return (0);
}
