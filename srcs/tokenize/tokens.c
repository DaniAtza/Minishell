/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:48:13 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 17:59:04 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *line, t_lexer *lexer)
{
	t_token	*token;
	size_t	len;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	len = lexer->i - lexer->token_start;
	token->value = ft_substr(line, lexer->token_start, len);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = lexer->type;
	token->next = NULL;
	return (token);
}

void	append_token(t_token *new_token, t_token **tokens_addr)
{
	t_token	*current;

	if (!*tokens_addr)
		*tokens_addr = new_token;
	else
	{
		current = *tokens_addr;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

void	free_tokens(t_token **tokens_addr)
{
	t_token	*current;
	t_token	*next;

	if (!*tokens_addr)
		return ;
	current = *tokens_addr;
	while (current)
	{
		next = current->next;
		if (current->type != WORD)
			free(current->value);
		free(current);
		current = next;
	}
	*tokens_addr = NULL;
}
