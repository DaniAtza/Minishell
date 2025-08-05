/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_words_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 02:58:26 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/05 03:39:02 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	swap_or_discard_expanded_arg(char **argv, size_t *i, t_word *word)
{
	size_t	j;

	if (word->string)
	{
		free(argv[*i]);
		argv[*i] = ft_strdup(word->string);
		if (argv[*i] == NULL)
			return (perror_return("swap_or_discard_expanded_arg: malloc", -1));
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

	i = 0;
	while (argv && argv[i])
	{
		if (contains_parameters(argv[i]) || contains_quotes(argv[i]))
		{
			if (init_word(&word, argv[i]) != 0)
				break ;
			if (expand_arg(&word, data) != 0)
				break ;
			if (swap_or_discard_expanded_arg(argv, &i, &word) != 0)
				break ;
			free_word(&word);
		}
		i++;
	}
	if (argv && argv[i])
	{
		free_word(&word);
		return (-1);
	}
	return (0);
}
