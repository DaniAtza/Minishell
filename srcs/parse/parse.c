/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:01:35 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:59:52 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_new_process(t_parser *parser)
{
	parser->process = create_process();
	if (!parser->process)
		return (-1);
	append_process(parser->process, &parser->processes);
	return (0);
}

static int	add_new_redirect(t_parser *parser)
{
	t_redirect	*new_redirect;

	new_redirect = create_redirect(parser->token, parser->token->next);
	if (!new_redirect)
		return (-1);
	append_redirect(new_redirect, &parser->process->redirects);
	return (0);
}

static int	add_new_arg(t_parser *parser)
{
	char	**reallocated_argv;

	reallocated_argv = append_arg(parser->token->value, parser->process->argv);
	if (!reallocated_argv)
		return (-1);
	parser->process->argv = reallocated_argv;
	return (0);
}

static int	handle_tokens(t_parser *parser)
{
	if (is_redirection(parser->token))
	{
		if (add_new_redirect(parser) != 0)
			return (-1);
		parser->token = parser->token->next->next;
	}
	else if (is_word(parser->token))
	{
		if (add_new_arg(parser) != 0)
			return (-1);
		parser->token = parser->token->next;
	}
	else if (is_pipe(parser->token))
	{
		if (add_new_process(parser) != 0)
			return (-1);
		parser->token = parser->token->next;
	}
	return (0);
}

t_process	*parse_tokens(t_token *tokens)
{
	t_parser	parser;

	if (!tokens)
		return (NULL);
	parser.token = tokens;
	parser.processes = NULL;
	if (add_new_process(&parser) != 0)
		return (NULL);
	while (parser.token)
	{
		if (handle_tokens(&parser) != 0)
		{
			free_processes(&parser.processes);
			return (NULL);
		}
	}
	return (parser.processes);
}
