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

int	cmd_not_found(char *cmd_pathname)
{
	char	*msg;

	msg = ft_strjoin(cmd_pathname, ": command not found\n");
	if (!msg)
		return (perror_return("malloc", 1));
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
	return (127);
}

int	perror_return_exec(char *cmd_pathname)
{
	struct stat		file_info;

	if (stat(cmd_pathname, &file_info) != 0)
	{
		perror(cmd_pathname);
		return (127);
	}
	else if (access(cmd_pathname, X_OK))
	{
		perror(cmd_pathname);
		return (126);
	}
	else if (S_ISDIR(file_info.st_mode))
		return (print_error_return(ft_strjoin(cmd_pathname, ": Is a directory"), 126));
	else if (errno == EINVAL)
		return (2);
	return (1);
}
