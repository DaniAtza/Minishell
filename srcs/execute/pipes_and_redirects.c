/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:56:22 by datienza          #+#    #+#             */
/*   Updated: 2025/07/26 18:42:18 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redirects(t_redirect *redir)
{
	int	fd;

	while (redir)
	{
		fd = open(redir->filename, redir->flags, redir->mode);
		if (fd == -1)
			return (perror(redir->filename), 1);
		if (dup2(fd, redir->target_fd) == -1)
			return (perror_return("dup2", -1));
		close(fd);
		redir = redir->next;
	}
	return (0);
}

void	setup_child_pipes(t_process *proc, int **pipes)
{
	if (proc->pipe_read_fd != -1)
	{
		if (dup2(proc->pipe_read_fd, STDIN_FILENO) == -1)
			perror_exit("dup2", 100);
	}
	if (proc->pipe_write_fd != -1)
	{
		if (dup2(proc->pipe_write_fd, STDOUT_FILENO) == -1)
			perror_exit("dup2", 100);
	}
	close_pipes(pipes);
}

int	save_stdio_fds(t_process *processes)
{
	processes->pipe_read_fd = dup(STDIN_FILENO);
	if (!processes->pipe_read_fd)
		return (print_error_return("dup", -1));
	processes->pipe_write_fd = dup(STDOUT_FILENO);
	if (!processes->pipe_write_fd)
		return (print_error_return("dup", -1));
	return (0);
}

int	restore_stdio_fds(t_process *processes)
{
	if (dup2(processes->pipe_read_fd, STDIN_FILENO) == -1)
		return (print_error_return("dup2", -1));
	close(processes->pipe_read_fd);
	if (dup2(processes->pipe_write_fd, STDOUT_FILENO) == -1)
		return (print_error_return("dup2", -1));
	close(processes->pipe_write_fd);
	return (0);
}
