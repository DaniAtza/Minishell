/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:42:45 by datienza          #+#    #+#             */
/*   Updated: 2025/05/29 21:43:06 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **cmd)
{
	if (!cmd)
		return (1);
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	return (0);
}
