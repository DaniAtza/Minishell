/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:40:31 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/08 19:33:51 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_list(char *envp[])
{
	t_env	*env_list;
	t_env	*current_node;
	t_env	*new_node;
	size_t	i;

	env_list = NULL;
	current_node = NULL;
	i = 0;
	while (envp && envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
		{
			free_env_list(&env_list);
			return (NULL);
		}
		if (current_node)
			current_node->next = new_node;
		else
			env_list = new_node;
		current_node = new_node;
		i++;
	}
	return (env_list);
}

void	free_env_list(t_env **env_list_addr)
{
	t_env	*current_node;
	t_env	*next_node;

	if (!*env_list_addr)
		return ;
	current_node = *env_list_addr;
	while (current_node)
	{
		next_node = current_node->next;
		free_env_node(&current_node);
		current_node = next_node;
	}
	*env_list_addr = NULL;
}

int	update_env_node(char *env_variable, t_env **env_list_addr)
{
	t_env	*prev_node;
	t_env	*current_node;
	t_env	*new_node;

	new_node = create_env_node(env_variable);
	if (!new_node)
		return (-1);
	prev_node = NULL;
	current_node = *env_list_addr;
	while (current_node)
	{
		if (ft_strcmp(current_node->name, new_node->name) == 0)
		{
			new_node->next = current_node->next;
			free_env_node(&current_node);
			break ;
		}
		prev_node = current_node;
		current_node = current_node->next;
	}
	if (prev_node)
		prev_node->next = new_node;
	else
		*env_list_addr = new_node;
	return (0);
}

void	delete_env_node(char *name, t_env **env_list_addr)
{
	t_env	*prev_node;
	t_env	*current_node;

	prev_node = NULL;
	current_node = *env_list_addr;
	while (current_node)
	{
		if (ft_strcmp(current_node->name, name) == 0)
		{
			if (prev_node)
				prev_node->next = current_node->next;
			else
				*env_list_addr = current_node->next;
			free_env_node(&current_node);
			return ;
		}
		prev_node = current_node;
		current_node = current_node->next;
	}
}

char	*search_env(char *name, t_env *env_list)
{
	t_env	*current_node;

	current_node = env_list;
	while (current_node)
	{
		if (ft_strcmp(current_node->name, name) == 0)
			return (current_node->value);
		current_node = current_node->next;
	}
	return (NULL);
}
