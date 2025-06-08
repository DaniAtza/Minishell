/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:54:18 by dagredan          #+#    #+#             */
/*   Updated: 2025/06/08 17:36:52 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_env **node_addr)
{
	t_env	*node;

	if (!*node_addr)
		return ;
	node = *node_addr;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	node_addr = NULL;
}

t_env	*create_env_node(char *env_variable)
{
	t_env	*node;
	size_t	separator_index;
	int		separator_not_found;

	separator_index = ft_strcspn(env_variable, "=");
	separator_not_found = separator_index == ft_strlen(env_variable);
	if (separator_not_found)
		return (NULL);
	node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_substr(env_variable, 0, separator_index);
	if (!node->name)
	{
		free_env_node(&node);
		return (NULL);
	}
	node->value = ft_strdup(env_variable + separator_index + 1);
	if (!node->value)
	{
		free_env_node(&node);
		return (NULL);
	}
	return (node);
}
