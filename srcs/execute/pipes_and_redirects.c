/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:56:22 by datienza          #+#    #+#             */
/*   Updated: 2025/06/27 22:57:42 by dagredan         ###   ########.fr       */
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
			return (print_and_return_error("dup2", 1));
		close(fd);
		if (redir->is_heredoc)
			unlink(redir->filename);
		redir = redir->next;
	}
	return (0);
}

void	setup_child_pipes(t_process *proc, int **pipes)
{
	if (proc->pipe_read_fd != -1)
	{
		if (dup2(proc->pipe_read_fd, STDIN_FILENO) == -1)
			error_exit("dup2", 1);
	}
	if (proc->pipe_write_fd != -1)
	{
		if (dup2(proc->pipe_write_fd, STDOUT_FILENO) == -1)
			error_exit("dup2", 1);
	}
	close_pipes(pipes);
}

int	save_stdio_fds(t_process *processes)
{
	processes->pipe_read_fd = dup(STDIN_FILENO);
	if (!processes->pipe_read_fd)
		return (print_and_return_error("dup", 1));
	processes->pipe_write_fd = dup(STDOUT_FILENO);
	if (!processes->pipe_write_fd)
		return (print_and_return_error("dup", 1));
	return (0);
}

int	restore_stdio_fds(t_process *processes)
{
	if (dup2(processes->pipe_read_fd, STDIN_FILENO) == -1)
		return (print_and_return_error("dup2", 1));
	close(processes->pipe_read_fd);
	if (dup2(processes->pipe_write_fd, STDOUT_FILENO) == -1)
		return (print_and_return_error("dup2", 1));
	close(processes->pipe_write_fd);
	return (0);
}
