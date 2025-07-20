/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_temp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:50:36 by datienza          #+#    #+#             */
/*   Updated: 2025/07/20 12:50:42 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	create_all_tmp_files(t_process *processes)
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
				create_tmp_file(redir);
			redir = redir->next;
		}
		ptr = ptr->next;
	}
}

