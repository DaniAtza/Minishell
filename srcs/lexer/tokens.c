/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:48:13 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/17 13:59:09 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *line, t_lexer *lexer, t_token_type type)
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
	token->type = type;
	token->next = NULL;
	return (token);
}

void	append_token(t_data *data, t_token *token)
{
	t_token	*current;

	if (!data->tokens)
	{
		data->tokens = token;
		return ;
	}
	current = data->tokens;
	while (current->next)
		current = current->next;
	current->next = token;
}

void	free_tokens(t_data *data)
{
	t_token	*current;
	t_token	*next;

	if (!data->tokens)
		return ;
	current = data->tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
