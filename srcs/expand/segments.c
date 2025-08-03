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

t_word	*create_word(char *word)
{
	t_word	*new_word;

	new_word = ft_calloc(1, sizeof(t_word));
	if (!new_word)
		return (NULL); // Handle memory allocation failure
	new_word->string = ft_strdup(word);
	if (!new_word->string)
	{
		free(new_word);
		return (NULL); // Handle memory allocation failure
	}
	create_word_segments(new_word);
	if (!new_word->segments)
	{
		free(new_word->string);
		free(new_word);
		return (NULL); // Handle memory allocation failure
	}
	return (new_word);
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
