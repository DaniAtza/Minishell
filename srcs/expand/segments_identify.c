/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:05:53 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/28 21:06:11 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_segm	*create_text_segment(char *ptr)
{
	t_segm	*new_segment;
	size_t	len;

	len = 0;
	while (ptr[len] != '\0')
	{
		if (ptr[len] == '$' && is_param_start(ptr[len + 1]))
			break ;
		else if (is_quote(ptr[len]))
			break ;
		len++;
	}
	new_segment = create_segment(ptr, len, TEXT);
	if (!new_segment)
		return (NULL);
	return (new_segment);
}

static t_segm	*create_quote_segment(char *ptr)
{
	t_segm	*new_segment;

	new_segment = create_segment(ptr, 1, QUOTE);
	if (!new_segment)
		return (NULL);
	return (new_segment);
}

static t_segm	*create_parameter_segment(char *ptr)
{
	t_segm	*new_segment;
	size_t	len;

	len = 1;
	if (ptr[len] == '?')
		len++;
	else
	{
		while (is_valid_name_char(ptr[len]))
			len++;
	}
	new_segment = create_segment(ptr, len, PARAMETER);
	if (!new_segment)
		return (NULL);
	return (new_segment);
}

void	identify_segments(t_word *word)
{
	t_segm	*new_segment;
	char	*ptr;

	ptr = word->string;
	while (*ptr != '\0')
	{
		if (*ptr == '$' && is_param_start(*(ptr + 1)))
			new_segment = create_parameter_segment(ptr);
		else if (is_quote(*ptr))
			new_segment = create_quote_segment(ptr);
		else
			new_segment = create_text_segment(ptr);
		if (!new_segment) // Handle error
		{
			printf("Error creating segment\n");
			return ;
		}
		append_segment(new_segment, word);
		ptr += new_segment->len;
	}
}

void	identify_quoted_segments(t_word *word)
{
	t_segm	*current;
	char	current_quote;
	char	found_quote;

	current_quote = '\0';
	current = word->segments;
	while (current)
	{
		if (current->type == QUOTE)
		{
			found_quote = current->start[0];
			if (current_quote == '\0')
			{
				current_quote = found_quote;
				current = current->next;
				continue ;
			}
			else if (found_quote == current_quote)
				current_quote = '\0';
		}
		if (current_quote == '\"')
			current->double_quoted = 1;
		else if (current_quote == '\'')
			current->single_quoted = 1;
		current = current->next;
	}
}
