/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:47:37 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:59:53 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_redirect_simple(t_redirect *redir, t_token *op, t_token *word)
{
	if (op->type == LESS)
	{
		redir->next = NULL;
		redir->filename = word->value;
		redir->flags = O_RDONLY;
		redir->mode = 0;
		redir->target_fd = STDIN_FILENO;
		redir->is_heredoc = 0;
		redir->delimiter = NULL;
		redir->expand_heredoc = 0;
	}
	else if (op->type == GREAT)
	{
		redir->next = NULL;
		redir->filename = word->value;
		redir->flags = O_WRONLY | O_TRUNC | O_CREAT;
		redir->mode = 0644;
		redir->target_fd = STDOUT_FILENO;
		redir->is_heredoc = 0;
		redir->delimiter = NULL;
		redir->expand_heredoc = 0;
	}
}

static void	init_redirect_double(t_redirect *redir, t_token *op, t_token *word)
{
	if (op->type == DLESS)
	{
		redir->next = NULL;
		redir->filename = NULL;
		redir->flags = O_RDWR | O_CREAT;
		redir->mode = 0600;
		redir->target_fd = STDIN_FILENO;
		redir->is_heredoc = 1;
		redir->delimiter = word->value;
		redir->expand_heredoc = 0;
	}
	else if (op->type == DGREAT)
	{
		redir->next = NULL;
		redir->filename = word->value;
		redir->flags = O_WRONLY | O_APPEND | O_CREAT;
		redir->mode = 0644;
		redir->target_fd = STDOUT_FILENO;
		redir->is_heredoc = 0;
		redir->delimiter = NULL;
		redir->expand_heredoc = 0;
	}
}

t_redirect	*create_redirect(t_token *redirection_operator, t_token *word)
{
	t_redirect	*new_redirect;

	new_redirect = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!new_redirect)
		return (NULL);
	if (redirection_operator->type == LESS)
		init_redirect_simple(new_redirect, redirection_operator, word);
	else if (redirection_operator->type == GREAT)
		init_redirect_simple(new_redirect, redirection_operator, word);
	else if (redirection_operator->type == DLESS)
		init_redirect_double(new_redirect, redirection_operator, word);
	else if (redirection_operator->type == DGREAT)
		init_redirect_double(new_redirect, redirection_operator, word);
	return (new_redirect);
}

void	append_redirect(t_redirect *new_redirect, t_redirect **redirects)
{
	t_redirect	*current;

	if (!*redirects)
		*redirects = new_redirect;
	else
	{
		current = *redirects;
		while (current->next)
			current = current->next;
		current->next = new_redirect;
	}
}

void	free_redirects(t_redirect **redirects)
{
	t_redirect	*current;
	t_redirect	*next;

	if (!*redirects)
		return ;
	current = *redirects;
	while (current)
	{
		next = current->next;
		if (current->is_heredoc && current->filename)
		{
			if (access(current->filename, F_OK) == 0)
				unlink(current->filename);
			free(current->filename);
		}
		free(current);
		current = next;
	}
	*redirects = NULL;
}
