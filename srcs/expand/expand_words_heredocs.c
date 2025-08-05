/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 03:57:25 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/05 03:57:36 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	swap_expanded_delimiter(t_redirect *redirect, t_word *word)
{
	free(redirect->delimiter);
	redirect->delimiter = ft_strdup(word->string);
	if (!redirect->delimiter)
	{
		free_word(word);
		return (perror_return("swap_expanded_delimiter: malloc", -1));
	}
	return (0);
}

static int	expand_delimiter(t_redirect *redirect, t_word *word)
{
	if (init_word(word, redirect->delimiter) != 0)
		return (-1);
	identify_quoted_segments(word);
	if (concat_word_segments(word) != 0)
		return (-1);
	if (swap_expanded_delimiter(redirect, word) != 0)
		return (-1);
	return (0);
}

int	expand_words_heredocs(t_redirect *redirects)
{
	t_word		word;
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (current->is_heredoc && contains_quotes(current->delimiter))
		{
			if (expand_delimiter(current, &word) != 0)
				return (-1);
			current->expand_heredoc = 0;
			free_word(&word);
		}
		else if (current->is_heredoc && !contains_quotes(current->delimiter))
			current->expand_heredoc = 1;
		current = current->next;
	}
	if (current)
	{
		free_word(&word);
		return (-1);
	}
	return (0);
}
