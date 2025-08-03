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
		return (perror_return("init_word: malloc", -1));
	create_word_segments(word);
	if (!word->segments)
	{
		free(word->string);
		word->string = NULL;
		return (-1);
	}
	return (0);
}

t_segm	*create_segment(char *start, size_t len, t_segm_type type)
{
	t_segm	*new_segment;

	new_segment = ft_calloc(1, sizeof(t_segm));
	if (!new_segment)
	{
		perror("create_segment: malloc");
		return (NULL);
	}
	new_segment->string = ft_substr(start, 0, len);
	if (!new_segment->string)
	{
		perror("create_segment: malloc");
		free(new_segment);
		return (NULL);
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

void	free_segments(t_word *word)
{
	t_segm	*current;
	t_segm	*next;

	current = word->segments;
	while (current)
	{
		next = current->next;
		if (current->string)
			free(current->string);
		free(current);
		current = next;
	}
	word->segments = NULL;
}

void	free_word(t_word *word)
{
	if (word->string)
	{
		free(word->string);
		word->string = NULL;
	}
	if (word->segments)
	{
		free_segments(word);
		word->segments = NULL;
	}
}
