/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_min.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:58:02 by datienza          #+#    #+#             */
/*   Updated: 2025/08/05 15:32:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_empty_env_array(void)
{
	char	**env_array;

	env_array = malloc(sizeof(char *) * 5);
	if (!env_array)
		return (NULL);
	env_array[0] = NULL;
	env_array[1] = NULL;
	env_array[2] = NULL;
	env_array[3] = NULL;
	env_array[4] = NULL;
	return (env_array);
}

char	**create_minimal_env(void)
{
	char	**minimal_env;

	minimal_env = create_empty_env_array();
	if (!minimal_env)
		return (NULL);
	minimal_env[0] = ft_strdup(DEF_PATH);
	if (!minimal_env[0])
		return (free_env_array(minimal_env), NULL);
	minimal_env[1] = create_pwd_var();
	if (!minimal_env[1])
		return (free_env_array(minimal_env), NULL);
	minimal_env[2] = ft_strdup(DEF_SHLVL);
	if (!minimal_env[2])
		return (free_env_array(minimal_env), NULL);
	minimal_env[3] = ft_strdup(DEF_UNDERSCORE);
	if (!minimal_env[3])
		return (free_env_array(minimal_env), NULL);
	return (minimal_env);
}

static int	search_var_exists(t_env **env_list_addr, char *name, char *var)
{
	char	*path_value;

	path_value = search_env(name, *env_list_addr);
	if (!path_value)
	{
		if (update_env_node(var, env_list_addr) == -1)
			return (-1);
	}
	return (0);
}

static int	search_pwd_exists(t_env **env_list_addr)
{
	char	*pwd_value;
	char	*pwd_var;

	pwd_value = search_env("PWD", *env_list_addr);
	if (!pwd_value)
	{
		pwd_var = create_pwd_var();
		if (!pwd_var)
			return (-1);
		if (update_env_node(pwd_var, env_list_addr) == -1)
		{
			free(pwd_var);
			return (-1);
		}
		free(pwd_var);
	}
	return (0);
}

int	ensure_essential_env_vars(t_env **env_list_addr)
{
	if (!env_list_addr)
		return (-1);
	if (search_var_exists(env_list_addr, "PATH", DEF_PATH) == -1)
		return (-1);
	if (search_var_exists(env_list_addr, "SHLVL", DEF_SHLVL) == -1)
		return (-1);
	if (search_pwd_exists(env_list_addr) == -1)
		return (-1);
	return (0);
}
