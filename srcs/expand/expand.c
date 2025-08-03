/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:35:08 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/27 14:39:50 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc_line(char *line, t_data *data)
{
	t_word	word;
	t_segm	*current;

	if (init_word(&word, line) != 00)
		return (NULL); // Handle malloc error
	current = word.segments;
	while (current)
	{
		current->double_quoted = 1;
		current = current->next;
	}
	expand_parameters(&word, data); // can fail
	concat_word_segments(&word); // can fail
	return (word.string);
}

static void	expand_heredoc_delimiters(t_redirect *redirects)
{
	t_word		word;
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (current->is_heredoc && contains_quotes(current->delimiter))
		{
			if (init_word(&word, current->delimiter) != 0)
				return ; // Handle malloc error
			identify_quoted_segments(&word);
			remove_quotes(&word);
			concat_word_segments(&word); // can fail
			current->delimiter = word.string; // TODO: memleak;
			current->expand_heredoc = 0;
			//free_word(&word); // TODO: free word segments and string
		}
		else if (current->is_heredoc && !contains_quotes(current->delimiter))
			current->expand_heredoc = 1;
		current = current->next;
	}
}

static void	expand_redirect_words(t_redirect *redirects, t_data *data)
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
				return ; // Handle malloc error
			identify_quoted_segments(&word);
			if (contains_parameters(word.string))
			{
				expand_parameters(&word, data); // Can fail
			}
			remove_quotes(&word);
			concat_word_segments(&word); // can fail
			current->filename = word.string; // TODO: memleak;
			//free_word(&word); // TODO: free word segments and string
		}
		current = current->next;
	}
}

static void	expand_argv_words(char **argv, t_data *data)
{
	t_word	word;
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (contains_parameters(argv[i]) || contains_quotes(argv[i]))
		{
			if (init_word(&word, argv[i]) != 0)
				return ; // Handle malloc error
			identify_quoted_segments(&word);
			if (contains_parameters(word.string))
			{
				expand_parameters(&word, data); // can fail
			}
			remove_quotes(&word);
			concat_word_segments(&word); // can fail
			argv[i] = word.string; // TODO: memleak;
			//free_word(&word); // TODO: free word segments and string
		}
		i++;
	}
}

int	expand_words(t_process *processes, t_data *data)
{
	t_process	*current;

	current = processes;
	while (current)
	{
		expand_argv_words(current->argv, data); // can fail
		expand_redirect_words(current->redirects, data); // can fail
		expand_heredoc_delimiters(current->redirects); // can fail
		current = current->next;
	}
	return (0);
}
