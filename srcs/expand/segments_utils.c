/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:54:35 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/02 13:54:35 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_segment(t_segm *segment)
{
	printf("Segment: ");
	printf("%.*s, ", (int)segment->len, segment->start);
	printf("len: %zu, ", segment->len);
	printf("double_quoted: %d, ", segment->double_quoted);
	printf("single_quoted: %d, ", segment->single_quoted);
	if (segment->type == TEXT)
		printf("type: TEXT\n");
	else if (segment->type == PARAMETER)
		printf("type: PARAMETER\n");
	else if (segment->type == QUOTE)
		printf("type: QUOTE\n");
}

void	print_word_segments(t_word *word)
{
	t_segm	*current;

	current = word->segments;
	while (current)
	{
		print_segment(current);
		current = current->next;
	}
}
