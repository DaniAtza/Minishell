/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:37:43 by datienza          #+#    #+#             */
/*   Updated: 2025/07/26 18:42:19 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(char *cmd)
{
	char	*msg;

	msg = ft_strjoin(cmd, ": command not found\n");
	if (!msg)
		perror_exit("malloc", 1);
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
	exit(127);
}
