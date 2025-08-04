/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:04:09 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:59:54 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_syntax(t_pipeline *pipeline)
{
	t_token	*current;

	current = pipeline->tokens;
	if (is_pipe(current))
		return (print_error_return(SYNTAX_ERROR, -1));
	while (current)
	{
		if (is_pipe(current))
		{
			if (!current->next || is_pipe(current->next))
				return (print_error_return(SYNTAX_ERROR, -1));
		}
		if (is_redirection(current))
		{
			if (!current->next || !is_word(current->next))
				return (print_error_return(SYNTAX_ERROR, -1));
		}
		current = current->next;
	}
	return (0);
}
