/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words_redirects.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 03:31:39 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/05 03:39:11 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	swap_expanded_filename(t_redirect *redirect, t_word *word)
{
	free(redirect->filename);
	if (!word->string)
		redirect->filename = NULL;
	else
	{
		redirect->filename = ft_strdup(word->string);
		if (redirect->filename == NULL)
			return (perror_return("swap_expanded_filename: malloc", -1));
	}
	return (0);
}

static int	expand_filename(t_word *word, t_data *data)
{
	identify_quoted_segments(word);
	if (contains_parameters(word->string))
	{
		if (expand_parameters(word, data) != 0)
			return (-1);
	}
	if (concat_word_segments(word) != 0)
		return (-1);
	return (0);
}

int	expand_words_redirects(t_redirect *redirects, t_data *data)
{
	t_word		word;
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (!current->is_heredoc && (contains_parameters(current->filename)
				|| contains_quotes(current->filename)))
		{
			if (init_word(&word, current->filename) != 0)
				break ;
			if (expand_filename(&word, data) != 0)
				break ;
			if (swap_expanded_filename(current, &word) != 0)
				break ;
			free_word(&word);
		}
		current = current->next;
	}
	if (current)
	{
		free_word(&word);
		return (-1);
	}
	return (0);
}
