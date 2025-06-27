/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:30:00 by datienza          #+#    #+#             */
/*   Updated: 2025/06/24 12:30:29 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_env(char *env_variable, t_env *env_list_addr)
{
	t_env	*current_node;

	current_node = env_list_addr;
	while (current_node)
	{
		if (ft_strcmp(current_node->name, env_variable) == 0)
			return (current_node->value);
		current_node = current_node->next;
	}
	return (NULL);
}

int	check_arg_error(char **arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
		i++;
	if ((i - 1) == 0)
		return (0);
	else if ((i - 1) >= 2)
		return (ft_putendl_fd("cd: too many arguments", STDERR_FILENO), 1);
	return (0);
}
