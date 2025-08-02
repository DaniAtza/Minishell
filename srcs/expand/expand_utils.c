/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:07:54 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/28 19:56:05 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * In the shell command language, a name is a word consisting solely of
 * underscores, digits, and alphabetics from the portable character set.
 * The first character of a name is not a digit.
 */
int	is_valid_name_first_char(char c)
{
	return (c == '_' || ft_isalpha(c));
}

/**
 * In the shell command language, a name is a word consisting solely of
 * underscores, digits, and alphabetics from the portable character set.
 * The first character of a name is not a digit.
 */
int	is_valid_name_char(char c)
{
	return (c == '_' || ft_isdigit(c) || ft_isalpha(c));
}

int	is_param_start(char c)
{
	return (is_valid_name_first_char(c) || c == '?');
}

int	contains_parameters(char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '$')
		{
			if (is_param_start(string[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	contains_quotes(char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (is_quote(string[i]))
			return (1);
		i++;
	}
	return (0);
}
