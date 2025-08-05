/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_min.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:58:02 by datienza          #+#    #+#             */
/*   Updated: 2025/08/05 12:34:12 by datienza         ###   ########.fr       */
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

static char	*create_pwd_var(void)
{
	char	*pwd;
	char	*pwd_var;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("/");
	if (!pwd)
		return (NULL);
	pwd_var = ft_strjoin("PWD=", pwd);
	free(pwd);
	return (pwd_var);
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
