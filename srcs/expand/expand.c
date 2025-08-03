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
	t_word	*word;
	t_segm	*current;

	word = create_word(line);
	identify_segments(word);
	current = word->segments;
	while (current)
	{
		current->double_quoted = 1;
		current = current->next;
	}
	expand_parameters(word, data);
	concat_word_segments(word);
	return (word->string);
}

static void	expand_heredoc_delimiters(t_redirect *redirects)
{
	t_word		*word;
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (current->is_heredoc && contains_quotes(current->delimiter))
		{
			word = create_word(current->delimiter);
			identify_segments(word);
			identify_quoted_segments(word);
			remove_quotes(word);
			concat_word_segments(word);
			current->delimiter = word->string; // TODO: memleak;
			current->expand_heredoc = 0;
		}
		else if (current->is_heredoc && !contains_quotes(current->delimiter))
			current->expand_heredoc = 1;
		current = current->next;
	}
}

static void	expand_redirect_words(t_redirect *redirects, t_data *data)
{
	t_word		*word;
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (!current->is_heredoc && (contains_parameters(current->filename)
			|| contains_quotes(current->filename)))
		{
			word = create_word(current->filename);
			identify_segments(word);
			identify_quoted_segments(word);
			if (contains_parameters(word->string))
			{
				expand_parameters(word, data);
				//split_word()
			}
			remove_quotes(word);
			concat_word_segments(word);
			current->filename = word->string; // TODO: memleak;
		}
		current = current->next;
	}
}

static void	expand_argv_words(char **argv, t_data *data)
{
	t_word	*word;
	size_t	i;

	i = 0;
	while (argv[i])
	{
		if (contains_parameters(argv[i]) || contains_quotes(argv[i]))
		{
			word = create_word(argv[i]);
			identify_segments(word);
			identify_quoted_segments(word);
			if (contains_parameters(word->string))
			{
				expand_parameters(word, data);
				//split_word()
			}
			remove_quotes(word);
			concat_word_segments(word);
			argv[i] = word->string; // TODO: memleak;
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
		expand_argv_words(current->argv, data);
		expand_redirect_words(current->redirects, data);
		expand_heredoc_delimiters(current->redirects);
		current = current->next;
	}
	return (0);
}
