/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_concat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:49:10 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/05 02:26:43 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_null_argument(t_word *word, char **new_string)
{
	if (word->segments->type == PARAMETER)
	{
		free(*new_string);
		*new_string = NULL;
	}
}

static int	is_unquoted_quote_segment(t_segm *segment)
{
	return (segment->type == QUOTE
		&& !segment->single_quoted && !segment->double_quoted);
}

static size_t	get_new_string_len(t_word *word)
{
	t_segm	*current;
	size_t	total_len;

	total_len = 0;
	current = word->segments;
	while (current)
	{
		if (is_unquoted_quote_segment(current))
		{
			current = current->next;
			continue ;
		}
		total_len += ft_strlen(current->string);
		current = current->next;
	}
	return (total_len);
}

int	concat_word_segments(t_word *word)
{
	t_segm	*current;
	size_t	total_len;
	char	*new_string;

	total_len = get_new_string_len(word);
	new_string = (char *)ft_calloc(total_len + 1, sizeof(char));
	if (!new_string)
		return (perror_return("concat_word_segments: malloc", -1));
	current = word->segments;
	while (current)
	{
		if (is_unquoted_quote_segment(current))
		{
			current = current->next;
			continue ;
		}
		ft_strlcat(new_string, current->string, total_len + 1);
		current = current->next;
	}
	if (ft_strlen(new_string) == 0)
		handle_null_argument(word, &new_string);
	free(word->string);
	word->string = new_string;
	return (0);
}
