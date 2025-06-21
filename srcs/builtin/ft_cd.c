/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:32:31 by datienza          #+#    #+#             */
/*   Updated: 2025/06/17 18:33:06 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_env(char *env_variable, t_env *env_list_addr)
{
	t_env	*current_node;

	current_node = env_list_addr;
	while (current_node)
	{
		if (ft_strcmp(current_node->name, env_variable) == 0)
			return (current_node->value);
		current_node = current_node->next;
	}
	return (NULL);
}

int	check_arg_error(char **arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
		i++;
	if ((i - 1) == 0)
		return (0);
	else if ((i - 1) >= 2)
		return(ft_putendl_fd("cd: too many arguments", STDERR_FILENO), 1);
	return (0);
}

int	update_working_directory(char *directory, t_env **env_list)
{
	char	*name_value;
	
	if (chdir(directory) == -1)
		return (perror(directory), -1);
	if (search_env("PWD", *env_list))
	{
		name_value = ft_strjoin("OLDPWD=", search_env("PWD", *env_list));
			if (!name_value)
				print_and_return_error("cd malloc", 1);
		update_env_node(name_value, env_list);
		free (name_value);
	}
	name_value = ft_strjoin("PWD=", directory);
		if (!name_value)
			print_and_return_error("cd malloc", 1);
	update_env_node(name_value, env_list);
	free (name_value);
	return (0);
}

int	ft_cd(char **arg, t_env **env_list)
{

	if (check_arg_error(arg))
		return (1);
	if (!arg[1])
	{
		if (!search_env("HOME", *env_list))
			return(ft_putendl_fd("cd: HOME not set", STDERR_FILENO), 1);
		if (update_working_directory(search_env("HOME", *env_list), env_list))
			return (1); 
	}
	else
	{
		if (update_working_directory(arg[1], env_list))
			return (1);
	}
	return (0);
}