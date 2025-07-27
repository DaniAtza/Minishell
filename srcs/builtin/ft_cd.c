/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:32:31 by datienza          #+#    #+#             */
/*   Updated: 2025/07/27 17:55:54 by datienza         ###   ########.fr       */
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
		return (perror_return("cd malloc", -1));
	update_env_node(name_value, &env_list);
	free(name_value);
	return (0);
}

static char	*get_current_directory(char *directory, char *old_pwd)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		if (ft_strcmp(directory, "..") == 0 && old_pwd)
			current_dir = ft_strjoin(old_pwd, "/..");
		else
			current_dir = ft_strdup(directory);
		if (!current_dir)
			return (NULL);
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory", STDERR_FILENO);
	}
	return (current_dir);
}

static int	handle_pwd_update(char *directory, char *old_pwd, t_data *data)
{
	char	*name_value;
	char	*current_dir;

	current_dir = get_current_directory(directory, old_pwd);
	if (!current_dir)
		return (-1);
	name_value = ft_strjoin("PWD=", current_dir);
	if (!name_value)
		return (free(current_dir), perror_return("cd malloc", -1));
	update_env_node(name_value, &data->env_list);
	if (data->current_pwd)
		free(data->current_pwd);
	data->current_pwd = ft_strdup(current_dir);
	if (!data->current_pwd)
		return (free(current_dir), free(name_value), -1);
	free(current_dir);
	free(name_value);
	return (0);
}

static int	update_working_dir(char *directory, t_data *data)
{
	char	*old_pwd;
	int		result;

	if (chdir(directory) == -1)
	{
		data->last_exit_status = 1;
		return (perror(directory), 1);
	}
	old_pwd = ft_strdup(data->current_pwd);
	if (!old_pwd)
		return (-1);
	result = handle_oldpwd_update(old_pwd, data->env_list);
	if (result != 0)
		return (free(old_pwd), result);
	result = handle_pwd_update(directory, old_pwd, data);
	if (result != 0)
		return (free(old_pwd), result);
	free(old_pwd);
	return (0);
}

static int	check_arg_error(char **argv, t_data *data)
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	if ((i - 1) == 0)
		return (0);
	else if ((i - 1) >= 2)
	{
		data->last_exit_status = 1;
		return (ft_putendl_fd("cd: too many arguments", STDERR_FILENO), 1);
	}
	return (0);
}

static int	handle_cd_cases(char **argv, t_data *data)
{
	int	result;

	if (!argv[1] || !(ft_strcmp(argv[1], "~")))
	{
		if (!search_env("HOME", data->env_list))
		{
			data->last_exit_status = 1;
			return (ft_putendl_fd("cd: HOME not set", STDERR_FILENO), 1);
		}
		result = update_working_dir(search_env("HOME", data->env_list), data);
	}
	else if (!(ft_strcmp(argv[1], "-")))
	{
		if (!search_env("OLDPWD", data->env_list))
		{
			data->last_exit_status = 1;
			return (ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO), 1);
		}
		result = update_working_dir(search_env("OLDPWD", data->env_list), data);
	}
	else
		result = update_working_dir(argv[1], data);
	return (result);
}

int	ft_cd(char **argv, t_data *data)
{
	int	result;

	result = check_arg_error(argv, data);
	if (result != 0)
		return (result);
	result = handle_cd_cases(argv, data);
	if (result != 0)
		return (result);
	data->last_exit_status = 0;
	return (0);
}
