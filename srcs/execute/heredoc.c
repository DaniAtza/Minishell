/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:26:36 by datienza          #+#    #+#             */
/*   Updated: 2025/07/07 20:15:14 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal = 0;
 
static int	write_heredoc(t_redirect *redir)
{
	int		fd;
	char	*line;

	fd = open(redir->filename, redir->flags, redir->mode); // TODO: Handle error
	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			break ;
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
	if (g_signal == SIGINT)
		return (130);
	else
		return(0);
}

static void	create_tmp_file(t_redirect *redir)
{
	char	*digits;
	char	*filename;
	int		i;

	i = 0;
	while (i < 1000000000)
	{
		digits = ft_itoa(i);
		if (!digits)
			error_exit("ft_itoa", 1); // TODO: Free memory properly
		filename = ft_strjoin("/tmp/.heredoc-", digits);
		free(digits);
		if (!filename)
			error_exit("ft_strjoin", 1); // TODO: Free memory properly
		if (access(filename, F_OK) == -1)
			break ;
		free(filename);
		i++;
	}
	if (i == 1000000000)
		error_exit("Error: Too many heredocs", 1);
	redir->filename = filename;
}

void	handle_heredocs(t_process *processes)
{
	t_process	*ptr;
	t_redirect	*redir;
	t_signal_backup	signal_backup;
	pid_t	pid;

	signal_backup = set_execution_signals();
	ptr = processes;
	while (ptr)
	{
		redir = ptr->redirects;
		while (redir)
		{
			if (redir->is_heredoc)
				create_tmp_file(redir);
			redir = redir->next;
		}
		ptr = ptr->next;
	}
	pid = fork();
	if (pid < 0)
		error_exit("fork", 1);
	if (pid == 0)
	{
		setup_heredoc_signals();		
		ptr = processes;
		while (ptr)
		{
			redir = ptr->redirects;
			while (redir)
			{
				if (redir->is_heredoc)
					if (write_heredoc(redir) == 130)
						break ;
				redir = redir->next;
			}
			ptr = ptr->next;
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
	restore_signals(signal_backup);
}