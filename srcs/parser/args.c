/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:00:19 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/23 23:29:51 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_array_len(char **array)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**append_arg(char *new_arg, char **args)
{
	char	**reallocated_args;
	size_t	len;

	len = ft_array_len(args);
	reallocated_args = ft_calloc(len + 2, sizeof(char *));
	if (!reallocated_args)
		return (NULL);
	ft_memmove(reallocated_args, args, len * sizeof(char *));
	reallocated_args[len] = new_arg;
	reallocated_args[len + 1] = NULL;
	free(args);
	return (reallocated_args);
}

void	free_args(char ***args_addr)
{
	free(*args_addr);
	*args_addr = NULL;
}
