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
		return (0);
	append_process(parser->process, &parser->processes);
	return (1);
}

static int	add_new_redirect(t_parser *parser)
{
	t_redirect	*new_redirect;

	new_redirect = create_redirect(parser->token, parser->token->next);
	if (!new_redirect)
		return (0);
	append_redirect(new_redirect, &parser->process->redirects);
	return (1);
}

static int	add_new_arg(t_parser *parser)
{
	char	**reallocated_argv;
	//char	*new_arg;

	/*
	new_arg = ft_strdup(parser->token->value);
	if (!new_arg)
		return (0);
	*/
	reallocated_argv = append_arg(parser->token->value, parser->process->argv);
	if (!reallocated_argv)
		return (0);
	parser->process->argv = reallocated_argv;
	return (1);
}

static int	handle_tokens(t_parser *parser)
{
	if (is_redirection(parser->token))
	{
		if (!add_new_redirect(parser))
			return (0);
		parser->token = parser->token->next->next;
	}
	else if (is_word(parser->token))
	{
		if (!add_new_arg(parser))
			return (0);
		parser->token = parser->token->next;
	}
	else if (is_pipe(parser->token))
	{
		if (!add_new_process(parser))
			return (0);
		parser->token = parser->token->next;
	}
	return (1);
}

t_process	*parse_tokens(t_token *tokens)
{
	t_parser	parser;

	if (!tokens)
		return (NULL);
	parser.token = tokens;
	parser.processes = NULL;
	if (!add_new_process(&parser))
		return (NULL);
	while (parser.token)
	{
		if (!handle_tokens(&parser))
		{
			free_processes(&parser.processes);
			return (NULL);
		}
	}
	return (parser.processes);
}
