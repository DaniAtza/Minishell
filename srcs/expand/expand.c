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

static void	expand_redirect_words(t_redirect *redirects, t_data *data)
{
	t_word		*word;
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (contains_parameters(current->filename)
			|| contains_quotes(current->filename))
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
			concat_segments(word);
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
			concat_segments(word);
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
		current = current->next;
	}
	return (0);
}
