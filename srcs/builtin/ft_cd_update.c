/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:53:34 by datienza          #+#    #+#             */
/*   Updated: 2025/08/04 18:56:38 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_oldpwd_update(char *old_pwd, t_env *env_list)
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

char	*get_current_directory(char *directory, char *old_pwd)
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

int	handle_pwd_update(char *directory, char *old_pwd, t_data *data)
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

int	update_working_dir(char *directory, t_data *data)
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
