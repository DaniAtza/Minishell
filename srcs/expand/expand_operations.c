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
	char	*name;
	char	*value;

	current = word->segments;
	while (current)
	{
		if (current->type == PARAMETER && !current->single_quoted)
		{
			name = ft_substr(current->start, 1, current->len - 1); // TODO: err
			if (name[0] == '?')
				value = ft_itoa(data->last_exit_status); // TODO: error and free
			else
				value = search_env(name, data->env_list);
			free(name);
			if (value)
			{
				current->start = value;
				current->len = ft_strlen(value);
				current->type = TEXT;
			}
		}
		current = current->next;
	}
}

void	remove_quotes(t_word *word)
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
