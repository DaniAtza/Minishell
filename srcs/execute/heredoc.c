/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:26:36 by datienza          #+#    #+#             */
/*   Updated: 2025/06/04 19:48:15 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

//TODO generate_tmpfilename();
void	apply_heredoc(t_redirect *redir)
{
	int	fd;

	fd = open(redir->filename, redir->flags, redir->mode);
	if (fd == -1)
		error_exit("heredoc_file", 1);
	write_heredoc(fd, redir->delimiter);
	close(fd);
	fd = open(redir->filename, redir->flags, redir->mode);
	if (fd == -1)
		error_exit("heredoc_file", 1);
	if (dup2(fd, redir->target_fd) == -1)
	{
		close(fd);
		error_exit("dup2", 1);
	}
	close(fd);
	unlink(redir->filename);
}
