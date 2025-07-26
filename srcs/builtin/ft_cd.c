/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:32:31 by datienza          #+#    #+#             */
/*   Updated: 2025/07/26 19:08:49 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_oldpwd_update(char *old_pwd, t_env *env_list)
{
	char	*name_value;

	if (!old_pwd)
		return (0);
	name_value = ft_strjoin("OLDPWD=", old_pwd);
	if (!name_value)
		return (perror_return("cd malloc", 1));
	update_env_node(name_value, &env_list);
	free(name_value);
	return (0);
}

static int	handle_pwd_update(char *directory, char *old_pwd, t_data *data)
{
	char	*name_value;
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		if (ft_strcmp(directory, "..") == 0 && old_pwd)
			current_dir = ft_strjoin(old_pwd, "/..");
		else
			current_dir = ft_strdup(directory);
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory", STDERR_FILENO);
	}
	name_value = ft_strjoin("PWD=", current_dir);
	if (!name_value)
		return (free(current_dir), perror_return("cd malloc", 1));
	update_env_node(name_value, &data->env_list);
	if (data->current_pwd)
		free(data->current_pwd);
	data->current_pwd = ft_strdup(current_dir);
	free(current_dir);
	free(name_value);
	return (0);
}

static int	update_working_dir(char *directory, t_data *data)
{
	char	*old_pwd;

	if (chdir(directory) == -1)
		return (perror(directory), 1);
	old_pwd = ft_strdup(data->current_pwd);
	if (handle_oldpwd_update(old_pwd, data->env_list) != 0)
		return (free(old_pwd), 1);
	if (handle_pwd_update(directory, old_pwd, data) != 0)
		return (free(old_pwd), 1);
	free(old_pwd);
	return (0);
}

static int	check_arg_error(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	if ((i - 1) == 0)
		return (0);
	else if ((i - 1) >= 2)
		return (ft_putendl_fd("cd: too many arguments", STDERR_FILENO), 1);
	return (0);
}

int	ft_cd(char **argv, t_data *data)
{
	if (check_arg_error(argv))
		return (1);
	if (!argv[1] || !(ft_strcmp(argv[1], "~")))
	{
		if (!search_env("HOME", data->env_list))
			return (ft_putendl_fd("cd: HOME not set", STDERR_FILENO), 1);
		if (update_working_dir(search_env("HOME", data->env_list), data))
			return (1);
	}
	else if (!(ft_strcmp(argv[1], "-")))
	{
		if (!search_env("OLDPWD", data->env_list))
			return (ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO), 1);
		if (update_working_dir(search_env("OLDPWD", data->env_list), data))
			return (1);
	}
	else
	{
		if (update_working_dir(argv[1], data))
			return (1);
	}
	return (0);
}
