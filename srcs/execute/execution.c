/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:14:23 by datienza          #+#    #+#             */
/*   Updated: 2025/06/04 19:49:03 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirects(t_redirect *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->is_heredoc)
			apply_heredoc(redir);
		else
		{
			fd = open(redir->filename, redir->flags, redir->mode);
			if (fd == -1)
				error_exit(redir->filename, 1);
			if (dup2(fd, redir->target_fd) == -1)
				error_exit("dup2", 1);
			close(fd);
		}
		redir = redir->next;
	}
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

void	execute_processes(t_data *data, t_env *env_list)
{
	t_process	*current;

	current = data->processes;
	while (current)
	{
		current->pid = fork();
		if (current->pid == -1)
			error_exit("fork", 1);
		if (current->pid == 0)
		{
			setup_child_pipes(current, data->pipes);
			if (current->redirects)
				apply_redirects(current->redirects);
			if (is_builtin(current->argv))
			{
				exe_builtin(current->argv, env_list);
				exit(0);
			}
			current->pathname = get_pathname(current->argv[0]);
			if (!current->pathname)
				cmd_not(current->argv[0]);
			execve(current->pathname, current->argv, NULL);
			error_exit(current->pathname, 1);
		}
		current = current->next;
	}
}

int	wait_processes(t_data *data)
{
	t_process	*current;
	int			status;

	close_pipes(data->pipes);
	current = data->processes;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		current = current->next;
	}
	return (status);
}

//TODO CORRECT RETURN NUM
int	execute_pipeline(t_data *data, t_env *env_list)
{
	execute_processes(data, env_list);
	return (wait_processes(data));
}
