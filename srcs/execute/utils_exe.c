/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:37:43 by datienza          #+#    #+#             */
/*   Updated: 2025/06/01 22:58:23 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *error, int n_exit)
{
	perror(error);
	exit(n_exit);
}

int	cmd_not(char *cmd)
{
	char	*msg;

	msg = ft_strjoin(cmd, ": command not found\n");
	if (!msg)
		error_exit("malloc", 1);
	ft_putstr_fd(msg, 2);
	free(msg);
	exit(127);
}
