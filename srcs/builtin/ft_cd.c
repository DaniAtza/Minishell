/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:32:31 by datienza          #+#    #+#             */
/*   Updated: 2025/06/24 14:07:39 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_oldpwd_update(char *old_pwd, t_env **env_list)
{
	char	*name_value;

	if (!old_pwd)
		return (0);
	name_value = ft_strjoin("OLDPWD=", old_pwd);
	if (!name_value)
		return (print_and_return_error("cd malloc", 1));
	update_env_node(name_value, env_list);
	free(name_value);
	return (0);
}

int	handle_pwd_update(char *directory, char *old_pwd, t_env **env_list)
{
	char	*name_value;
	char	*current_dir;

	current_dir = getcwd(NULL, 0); // TODO
	if (!current_dir)
	{
		if (ft_strcmp(directory, "..") == 0 && old_pwd)
			current_dir = ft_strjoin(old_pwd, "/..");
		else
			current_dir = ft_strdup(directory);
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot\
access parent directories: No such file or directory", STDERR_FILENO);
	}
	name_value = ft_strjoin("PWD=", current_dir);
	if (!name_value)
		return (free(current_dir), print_and_return_error("cd malloc", 1));
	update_env_node(name_value, env_list);
	if (g_current_pwd) // TODO
		free(g_current_pwd);
	g_current_pwd = ft_strdup(current_dir);
	free(current_dir);
	free(name_value);
	return (0);
}

int	update_working_directory(char *directory, t_env **env_list)
{
	char	*old_pwd;

	if (chdir(directory) == -1)
		return (perror(directory), 1);
	old_pwd = ft_strdup(g_current_pwd); // TODO
	if (handle_oldpwd_update(old_pwd, env_list) != 0)
		return (free(old_pwd), 1);
	if (handle_pwd_update(directory, old_pwd, env_list) != 0)
		return (free(old_pwd), 1);
	free(old_pwd);
	return (0);
}

int	ft_cd(char **arg, t_env **env_list)
{
	if (check_arg_error(arg))
		return (1);
	if (!arg[1] || !(ft_strcmp(arg[1], "~")))
	{
		if (!search_env("HOME", *env_list))
			return (ft_putendl_fd("cd: HOME not set", STDERR_FILENO), 1);
		if (update_working_directory(search_env("HOME", *env_list), env_list))
			return (1);
	}
	else if (!(ft_strcmp(arg[1], "-")))
	{
		if (!search_env("OLDPWD", *env_list))
			return (ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO), 1);
		if (update_working_directory(search_env("OLDPWD", *env_list), env_list))
			return (1);
	}
	else
	{
		if (update_working_directory(arg[1], env_list))
			return (1);
	}
	return (0);
}