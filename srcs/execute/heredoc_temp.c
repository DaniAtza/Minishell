/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_temp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:50:36 by datienza          #+#    #+#             */
/*   Updated: 2025/07/21 21:54:29 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_name_tmp_file(t_redirect *redir)
{
	char	*digits;
	char	*filename;
	int		i;

	i = 0;
	while (i < 1000000000)
	{
		digits = ft_itoa(i);
		if (!digits)
			return (print_and_return_error("ft_itoa", -1));
		filename = ft_strjoin("/tmp/.heredoc-", digits);
		free(digits);
		if (!filename)
			return (print_and_return_error("ft_strjoin", -1));
		if (access(filename, F_OK) == -1)
			break ;
		free(filename);
		i++;
	}
	if (i == 1000000000)
		return (print_and_return_error("Error: Too many heredocs", -1));
	redir->filename = filename;
	return (0);
}

int	create_all_tmp_files(t_process *processes)
{
	t_process	*ptr;
	t_redirect	*redir;
	int			fd;

	ptr = processes;
	while (ptr)
	{
		redir = ptr->redirects;
		while (redir)
		{
			if (redir->is_heredoc)
			{
				if (search_name_tmp_file(redir) == -1)
					return (-1);
				fd = open(redir->filename, redir->flags, redir->mode);
				if (fd == -1)
					return (print_and_return_error("Open filename \
heredoc", -1));
				close(fd);
			}
			redir = redir->next;
		}
		ptr = ptr->next;
	}
	return (0);
}
