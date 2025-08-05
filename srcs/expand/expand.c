/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:35:08 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/05 03:58:03 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc_line(char *line, t_data *data)
{
	t_word	word;
	t_segm	*current;

	if (init_word(&word, line) != 0)
		return (NULL);
	free(line);
	current = word.segments;
	while (current)
	{
		current->double_quoted = 1;
		current = current->next;
	}
	if (expand_parameters(&word, data) != 0)
	{
		free_word(&word);
		return (NULL);
	}
	if (concat_word_segments(&word) != 0)
	{
		free_word(&word);
		return (NULL);
	}
	free_segments(&word);
	return (word.string);
}

int	expand_words(t_process *processes, t_data *data)
{
	t_process	*current;

	current = processes;
	while (current)
	{
		if (expand_words_argv(current->argv, data) != 0)
			return (-1);
		if (expand_words_redirects(current->redirects, data) != 0)
			return (-1);
		if (expand_words_heredocs(current->redirects) != 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
