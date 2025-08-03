/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 05:25:17 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/31 05:26:37 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_word(t_word *word, char *string)
{
	ft_memset(word, 0, sizeof(t_word));
	word->string = ft_strdup(string);
	if (!word->string)
		return (-1); // Handle memory allocation failure
	create_word_segments(word);
	if (!word->segments)
	{
		free(word->string);
		return (-1); // Handle memory allocation failure
	}
	return (0);
}

t_segm	*create_segment(char *start, size_t len, t_segm_type type)
{
	t_segm	*new_segment;

	new_segment = ft_calloc(1, sizeof(t_segm));
	if (!new_segment)
		return (NULL); // Handle memory allocation failure
	new_segment->string = ft_substr(start, 0, len);
	if (!new_segment->string)
	{
		free(new_segment);
		return (NULL); // Handle memory allocation failure
	}
	new_segment->type = type;
	return (new_segment);
}

void	append_segment(t_segm *new_segment, t_word *word)
{
	t_segm	*current;

	if (!word->segments)
		word->segments = new_segment;
	else
	{
		current = word->segments;
		while (current->next)
			current = current->next;
		current->next = new_segment;
	}
}
