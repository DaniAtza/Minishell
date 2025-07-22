/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:26:36 by datienza          #+#    #+#             */
/*   Updated: 2025/07/21 22:25:46 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_heredoc(t_redirect *redir)
{
	int		fd;
	char	*line;

	fd = open(redir->filename, redir->flags, redir->mode);
	if (fd == -1)
		exit(-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->delimiter) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	return (0);
}

static void	write_all_heredocs(t_process *processes)
{
	t_process	*ptr;
	t_redirect	*redir;

	ptr = processes;
	while (ptr)
	{
		redir = ptr->redirects;
		while (redir)
		{
			if (redir->is_heredoc)
				write_heredoc(redir);
			redir = redir->next;
		}
		ptr = ptr->next;
	}
}

static int	execute_heredoc_child(t_process *processes)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (print_and_return_error("fork", -1));
	if (pid == 0)
	{
		setup_heredoc_signals();
		write_all_heredocs(processes);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		else if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

int	handle_heredocs(t_data *data, t_process *processes)
{
	t_signal_backup	signal_backup;

	signal_backup = set_execution_signals();
	if (create_all_tmp_files(processes) == -1)
	{
		restore_signals(signal_backup);
		return (-1);
	}
	data->last_exit_status = execute_heredoc_child(processes);
	restore_signals(signal_backup);
	return (data->last_exit_status);
}
