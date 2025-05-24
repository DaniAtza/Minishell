/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:04:09 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/20 12:29:02 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_syntax(t_data *data)
{
	t_token	*tmp;

	if (!data || !data->tokens)
		return (-1);
	tmp = data->tokens;
	if (is_pipe(tmp))
		return (-1);
	while (tmp)
	{
		if (is_pipe(tmp))
		{
			if (!tmp->next || is_pipe(tmp->next))
				return (-1);
		}
		if (is_redirection(tmp))
		{
			if (!tmp->next || !is_word(tmp->next))
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}
