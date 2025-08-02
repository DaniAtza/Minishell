/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_segments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:49:10 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/02 13:49:12 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_total_segments_len(t_word *word)
{
	t_segm	*current;
	size_t	total_len;

	total_len = 0;
	current = word->segments;
	while (current)
	{
		total_len += current->len;
		current = current->next;
	}
	return (total_len);
}

void	concat_segments(t_word *word)
{
	t_segm	*current;
	size_t	total_len;
	char	*new_string;
	char	*new_string_ptr;

	total_len = get_total_segments_len(word);
	new_string = ft_calloc(total_len + 1, sizeof(char));
	if (!new_string) // TODO: handle error
		return ;
	new_string_ptr = new_string;
	current = word->segments;
	while (current)
	{
		ft_strlcpy(new_string_ptr, current->start, current->len + 1);
		new_string_ptr += current->len;
		current = current->next;
	}
	free(word->string);
	word->string = new_string;
}
