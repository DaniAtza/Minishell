/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:32:31 by datienza          #+#    #+#             */
/*   Updated: 2025/08/04 18:18:38 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
