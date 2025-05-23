/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:01:35 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/22 20:43:51 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_new_process(t_parser *parser)
{
	parser->process = create_process();
	if (!parser->process)
		return (0);
	append_process(parser->process, &parser->processes);
	return (1);
}

t_process	*parse_tokens(t_token *tokens)
{
	t_parser	parser;

	if (!tokens)
		return (NULL);
	parser.token = tokens;
	parser.processes = NULL;
	if (!handle_new_process(&parser))
		return (NULL);
	while (parser.token)
	{
		if (is_redirection(parser.token))
			parser.token = parser.token->next; // TODO
		else if (is_word(parser.token))
			parser.token = parser.token->next; // TODO
		else if (is_pipe(parser.token))
		{
			if (!handle_new_process(&parser))
				return (free_processes(&parser.processes), NULL);
			parser.token = parser.token->next;
		}
	}
	return (parser.processes);
}
