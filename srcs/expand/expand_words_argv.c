/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 02:58:26 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/05 02:59:44 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	insert_or_discard_expanded_arg(char **argv, size_t *i, t_word *word)
{
	size_t	j;

	if (word->string)
	{
		free(argv[*i]);
		argv[*i] = ft_strdup(word->string);
		if (argv[*i] == NULL)
			return (perror_return("insert_expanded_argv_word: malloc", -1));
	}
	else
	{
		free(argv[*i]);
		j = *i;
		while (argv[j + 1])
		{
			argv[j] = argv[j + 1];
			j++;
		}
		argv[j] = NULL;
		(*i)--;
	}
	return (0);
}

static int	expand_arg(t_word *word, t_data *data)
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

int	expand_words_argv(char **argv, t_data *data)
{
	t_word	word;
	size_t	i;

	if (argv == NULL)
		return (0);
	i = 0;
	while (argv[i])
	{
		if (contains_parameters(argv[i]) || contains_quotes(argv[i]))
		{
			if (init_word(&word, argv[i]) != 0)
				return (-1);
			if (expand_arg(&word, data) != 0)
				break ;
			if (insert_or_discard_expanded_arg(argv, &i, &word) != 0)
				break ;
			free_word(&word);
		}
		i++;
	}
	if (argv[i])
		free_word(&word);
	return (0);
}
