/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
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

char	**append_arg(char *new_arg, char **argv)
{
	char	**reallocated_argv;
	size_t	len;

	len = ft_array_len(argv);
	reallocated_argv = ft_calloc(len + 2, sizeof(char *));
	if (!reallocated_argv)
		return (NULL);
	ft_memmove(reallocated_argv, argv, len * sizeof(char *));
	reallocated_argv[len] = new_arg;
	reallocated_argv[len + 1] = NULL;
	free(argv);
	return (reallocated_argv);
}

void	free_argv(char ***argv_addr)
{
	if (!*argv_addr)
		return ;
	free(*argv_addr);
	*argv_addr = NULL;
}
