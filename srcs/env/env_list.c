/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:40:31 by dagredan          #+#    #+#             */
/*   Updated: 2025/06/08 17:36:51 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_env_node(t_env *new_node, t_env **env_list)
{
	t_env	*current;

	if (!*env_list)
		*env_list = new_node;
	else
	{
		current = *env_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

t_env	*create_env_list(char *envp[])
{
	t_env	*env_list;
	t_env	*new_node;
	size_t	i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
		{
			free_env_list(&env_list);
			return (NULL);
		}
		append_env_node(new_node, &env_list);
		i++;
	}
	return (env_list);
}

void	free_env_list(t_env **env_list)
{
	t_env	*current;
	t_env	*next;

	if (!*env_list)
		return ;
	current = *env_list;
	while (current)
	{
		next = current->next;
		free_env_node(&current);
		current = next;
	}
	*env_list = NULL;
}
