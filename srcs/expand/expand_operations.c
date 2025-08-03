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

int	expand_parameters(t_word *word, t_data *data)
{
	t_segm	*current;
	char	*name;

	current = word->segments;
	while (current)
	{
		if (current->type == PARAMETER && !current->single_quoted)
		{
			name = current->string;
			if (name[1] == '?')
				current->string = ft_itoa(data->last_exit_status);
			else
			{
				current->string = search_env(name + 1, data->env_list);
				if (!current->string)
					current->string = ft_strdup("");
				else
					current->string = ft_strdup(current->string);
			}
			free(name);
			if (!current->string)
				return (perror_return("expand_parameters: malloc", -1));
		}
		current = current->next;
	}
	return (0);
}

void	remove_quotes(t_word *word) // TODO: memory leak de segments
{
	t_segm	*previous;
	t_segm	*current;
	t_segm	*to_free;

	previous = NULL;
	current = word->segments;
	while (current)
	{
		if (current->type == QUOTE
			&& !current->single_quoted && !current->double_quoted)
		{
			to_free = current;
			if (previous)
			{
				previous->next = current->next;
				current = current->next;
				free(to_free->string);
				free(to_free);
				continue ;
			}
			else
			{
				word->segments = current->next;
				current = current->next;
				free(to_free->string);
				free(to_free);
				continue ;
			}
		}
		previous = current;
		current = current->next;
	}
}
