/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:39:55 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/27 14:54:48 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_parameters(t_word *word, t_data *data)
{
	t_segm	*current;
	char	*value;

	current = word->segments;
	while (current)
	{
		if (current->type == PARAMETER && !current->single_quoted)
		{
			if (current->string[1] == '?')
				current->string = ft_itoa(data->last_exit_status);
			else
			{
				value = search_env(current->string + 1, data->env_list);
				if (!value) // This means that the variable is not found
					current->string = ft_strdup("");
				else
					current->string = ft_strdup(value);
			}
			if (!current->string)
				return ; // Handle malloc error
		}
		current = current->next;
	}
}

void	remove_quotes(t_word *word) // TODO: memory leak de segments
{
	t_segm	*previous;
	t_segm	*current;

	previous = NULL;
	current = word->segments;
	while (current)
	{
		if (current->type == QUOTE
			&& !current->single_quoted && !current->double_quoted)
		{
			if (previous)
			{
				previous->next = current->next;
				current = current->next;
				continue ;
			}
			else
			{
				word->segments = current->next;
				current = current->next;
				continue ;
			}
		}
		previous = current;
		current = current->next;
	}
}
