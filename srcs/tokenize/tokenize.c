/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:48:28 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 17:59:03 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	seek_next_quote(t_lexer *lexer, char *line, char quote)
{
	lexer->i++;
	while (line[lexer->i] != quote)
	{
		if (line[lexer->i] == '\0')
		{
			ft_putstr_fd("Syntax error: Unmatched quotes\n", 2);
			return (0);
		}
		lexer->i++;
	}
	return (1);
}

static t_token	*tokenize_word(t_lexer *lexer, char *line)
{
	lexer->token_start = lexer->i;
	while (line[lexer->i] != '\0')
	{
		if (is_special(line[lexer->i]))
			break ;
		if (is_quote(line[lexer->i]))
			if (!seek_next_quote(lexer, line, line[lexer->i]))
				return (NULL);
		lexer->i++;
	}
	lexer->type = WORD;
	return (create_token(line, lexer));
}

static void	discard_blank(t_lexer *lexer, char *line)
{
	while (is_blank(line[lexer->i]))
		lexer->i++;
}

static t_token	*tokenize_operator(t_lexer *lexer, char *line)
{
	lexer->token_start = lexer->i;
	if (line[lexer->i] == '<' && line[lexer->i + 1] == '<')
		lexer->type = DLESS;
	else if (line[lexer->i] == '<')
		lexer->type = LESS;
	else if (line[lexer->i] == '>' && line[lexer->i + 1] == '>')
		lexer->type = DGREAT;
	else if (line[lexer->i] == '>')
		lexer->type = GREAT;
	else if (line[lexer->i] == '|')
		lexer->type = VLINE;
	if (lexer->type == LESS || lexer->type == GREAT || lexer->type == VLINE)
		lexer->i++;
	else if (lexer->type == DLESS || lexer->type == DGREAT)
		lexer->i += 2;
	return (create_token(line, lexer));
}

t_token	*tokenize_line(char *line)
{
	t_lexer	lexer;
	t_token	*new_token;

	ft_memset(&lexer, 0, sizeof(t_lexer));
	while (line[lexer.i] != '\0' && line[lexer.i] != '#')
	{
		if (is_blank(line[lexer.i]))
		{
			discard_blank(&lexer, line);
			continue ;
		}
		if (is_operator(line[lexer.i]))
			new_token = tokenize_operator(&lexer, line);
		else
			new_token = tokenize_word(&lexer, line);
		if (!new_token)
		{
			free_tokens(&lexer.tokens);
			ft_putendl_fd("Error: tokenize_line", 2);
			return (NULL);
		}
		append_token(new_token, &lexer.tokens);
	}
	return (lexer.tokens);
}
