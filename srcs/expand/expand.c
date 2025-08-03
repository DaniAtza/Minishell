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

static int	expand_heredoc_delimiters(t_redirect *redirects)
{
	t_word		word;
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (current->is_heredoc && contains_quotes(current->delimiter))
		{
			if (init_word(&word, current->delimiter) != 0)
				return (-1); 
			identify_quoted_segments(&word);
			remove_quotes(&word);
			if (concat_word_segments(&word) != 0)
			{
				free_word(&word);
				return (-1);
			}
			free(current->delimiter);
			current->delimiter = ft_strdup(word.string);
			if (!current->delimiter)
			{
				free_word(&word);
				return (perror_return("expand_heredoc_delimiters: strdup", -1));
			}
			current->expand_heredoc = 0;
			free_word(&word);
		}
		else if (current->is_heredoc && !contains_quotes(current->delimiter))
			current->expand_heredoc = 1;
		current = current->next;
	}
	return (0);
}

static int	expand_redirect_words(t_redirect *redirects, t_data *data)
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
				return (-1);
			identify_quoted_segments(&word);
			if (contains_parameters(word.string))
			{
				if (expand_parameters(&word, data) != 0)
				{
					free_word(&word);
					return (-1);
				}
			}
			remove_quotes(&word);
			if (concat_word_segments(&word) != 0)
			{
				free_word(&word);
				return (-1);
			}
			free(current->filename);
			current->filename = ft_strdup(word.string);
			if (current->filename == NULL)
			{
				free_word(&word);
				return (perror_return("expand_redirect_words: strdup", -1));
			}
			free_word(&word);
		}
		current = current->next;
	}
	return (0);
}

static int	expand_argv_words(char **argv, t_data *data)
{
	t_word	word;
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (contains_parameters(argv[i]) || contains_quotes(argv[i]))
		{
			if (init_word(&word, argv[i]) != 0)
				return (-1);
			identify_quoted_segments(&word);
			if (contains_parameters(word.string))
			{
				if (expand_parameters(&word, data) != 0)
				{
					free_word(&word);
					return (-1);
				}
			}
			remove_quotes(&word);
			if (concat_word_segments(&word) != 0)
			{
				free_word(&word);
				return (-1);
			}
			free(argv[i]);
			argv[i] = ft_strdup(word.string);
			if (argv[i] == NULL)
			{
				free_word(&word);
				return (perror_return("expand_argv_words: strdup", -1));
			}
			free_word(&word);
		}
		i++;
	}
	return (0);
}

int	expand_words(t_process *processes, t_data *data)
{
	t_process	*current;

	current = processes;
	while (current)
	{
		if (expand_argv_words(current->argv, data) != 0)
			return (-1);
		if (expand_redirect_words(current->redirects, data) != 0)
			return (-1);
		if (expand_heredoc_delimiters(current->redirects) != 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
