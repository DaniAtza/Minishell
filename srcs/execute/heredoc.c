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

static void	write_heredoc(t_redirect *redir)
{
	int		fd;
	char	*line;

	fd = open(redir->filename, redir->flags, redir->mode); // TODO: Handle error
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ; // TODO: Handle EOF or error
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, redir->delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
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
	t_redirect	*redir;

	while (processes)
	{
		redir = processes->redirects;
		while (redir)
		{
			if (redir->is_heredoc)
			{
				create_tmp_file(redir);
				write_heredoc(redir);
			}
			redir = redir->next;
		}
		processes = processes->next;
	}
}
