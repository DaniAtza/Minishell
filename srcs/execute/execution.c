/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:14:23 by datienza          #+#    #+#             */
/*   Updated: 2025/05/24 18:14:30 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO free_mem
void	apply_redirects(t_redirect *redir)
{
	int	fd;

	while (redir)
	{		
		//TODO heredoc
		fd = open(redir->filename, redir->flags, redir->mode);
		if (fd == -1)
		{
			perror(redir->filename);
			exit(1);
		}
		if (dup2(fd, redir->target_fd) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(fd);
		redir = redir->next;
	}
}

void	setup_child_pipes(t_process *proc, int **pipes)
{
	if (proc->pipe_read_fd != -1)
	{
		if (dup2(proc->pipe_read_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (proc->pipe_write_fd != -1)
	{
		if (dup2(proc->pipe_write_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	
	close_pipes(pipes);
}

int	execute_pipeline(t_data *data)
{
	t_process	*current;
	pid_t		pid;
	int			process_index;
	int			status;

	current = data->processes;
	process_index = 0;
	
	while (current)
	{
		pid = fork();
		if (pid == -1)
		{
		perror("fork");
		exit(1);
		}
		if (pid == 0)
		{
			setup_child_pipes(current, data->pipes);
			if (current->redirects)
				apply_redirects(current->redirects);
			//TODO PATH
			//TODO command not found:
			//if (is_builtin(procdcess->pathname))
				//execute_builtin(process->pathname)
			execve(current->pathname, current->argv, NULL);
			perror(current->pathname);
			exit(1);
		}
		current->pid = pid;
		current = current->next;
		process_index++;
	}

	waitpid(pid, &status, 0);
	
	return (0);
}
