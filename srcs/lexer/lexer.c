/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:48:28 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/17 13:58:48 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	seek_next_quote(t_lexer *lexer, char *line, char quote)
{
	lexer->i++;
	while (line[lexer->i] != quote)
	{
		if (line[lexer->i] == '\0')
			// TODO: Handle fail. "Syntax error: Unmatched quotes"
			return (-1);
		lexer->i++;
	}
	return (0);
}

static int	tokenize_word(t_data *data, t_lexer *lexer, char *line)
{
	t_token	*token;

	lexer->token_start = lexer->i;
	while (line[lexer->i] != '\0')
	{
		if (is_special(line[lexer->i]))
			break ;
		if (is_quote(line[lexer->i]))
			seek_next_quote(lexer, line, line[lexer->i]); // TODO: Handle fail
		lexer->i++;
	}
	token = create_token(line, lexer, WORD);
	if (!token)
		return (-1); // TODO: Handle fail
	append_token(data, token);
	return (0);
}

static void	discard_blank(t_lexer *lexer, char *line)
{
	while (is_blank(line[lexer->i]))
		lexer->i++;
}

static int	tokenize_operator(t_data *data, t_lexer *lexer, char *line)
{
	t_token			*token;
	t_token_type	type;

	lexer->token_start = lexer->i;
	if (line[lexer->i] == '<' && line[lexer->i + 1] == '<')
		type = DLESS;
	else if (line[lexer->i] == '<')
		type = LESS;
	else if (line[lexer->i] == '>' && line[lexer->i + 1] == '>')
		type = DGREAT;
	else if (line[lexer->i] == '>')
		type = GREAT;
	else if (line[lexer->i] == '|')
		type = VLINE;
	if (type == LESS || type == GREAT || type == VLINE)
		lexer->i++;
	else if (type == DLESS || type == DGREAT)
		lexer->i += 2;
	token = create_token(line, lexer, type);
	if (!token)
		return (-1); // TODO: Handle fail
	append_token(data, token);
	return (0);
}

void	tokenize_line(t_data *data, char *line)
{
	t_lexer	lexer;

	ft_memset(&lexer, 0, sizeof(t_lexer));
	while (line[lexer.i] != '\0')
	{
		if (is_operator(line[lexer.i]))
			tokenize_operator(data, &lexer, line); // TODO: Handle fail
		else if (is_blank(line[lexer.i]))
			discard_blank(&lexer, line);
		else if (line[lexer.i] == '#')
			break ;
		else
			tokenize_word(data, &lexer, line); // TODO: Handle fail
	}
	return ;
}
