/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:40:57 by datienza          #+#    #+#             */
/*   Updated: 2025/08/03 11:04:21 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_env_nodes(t_env *env_list)
{
	size_t	count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->value)
			count++;
		current = current->next;
	}
	return (count);
}

static char	*create_env_string(t_env *node)
{
	char	*env_str;
	size_t	name_len;
	size_t	value_len;
	size_t	total_len;

	if (!node->name || !node->value)
		return (NULL);
	name_len = ft_strlen(node->name);
	value_len = ft_strlen(node->value);
	total_len = name_len + 1 + value_len + 1;
	env_str = (char *)malloc(total_len);
	if (!env_str)
		return (NULL);
	ft_strlcpy(env_str, node->name, total_len);
	ft_strlcat(env_str, "=", total_len);
	ft_strlcat(env_str, node->value, total_len);
	return (env_str);
}

void	free_env_array(char **env_array)
{
	size_t	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

static int	fill_env_array(char **env_array, t_env *env_list, size_t count)
{
	t_env	*current;
	size_t	i;

	current = env_list;
	i = 0;
	while (current && i < count)
	{
		if (current->value)
		{
			env_array[i] = create_env_string(current);
			if (!env_array[i])
			{
				free_env_array(env_array);
				return (0);
			}
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (1);
}

char	**env_list_to_array(t_env *env_list)
{
	char	**env_array;
	size_t	count;

	count = count_env_nodes(env_list);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	if (!fill_env_array(env_array, env_list, count))
		return (NULL);
	return (env_array);
}
