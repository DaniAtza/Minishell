/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:47:18 by datienza          #+#    #+#             */
/*   Updated: 2025/07/04 22:19:12 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
}

static void	print_export_error(char *arg)
{
	char	*error1;
	char	*error2;

	error1 = ft_strjoin("export: `", arg);
	if (!error1)
		return ;
	error2 = ft_strjoin(error1, "': not a valid identifier");
	free(error1);
	if (!error2)
		return ;
	ft_putendl_fd(error2, STDERR_FILENO);
	free(error2);
}

static int	validate_variable_name(char *arg)
{
	size_t	i;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (print_export_error(arg), 1);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (print_export_error(arg), 1);
		i++;
	}
	return (0);
}

int	ft_export(char **cmd, t_env *env_list)
{
	size_t	i;

	if (!cmd[1])
		print_export_list(env_list);
	i = 1;
	while (cmd[i])
	{
		if (!validate_variable_name(cmd[i]))
			update_env_node(cmd[i], &env_list);
		i++;
	}
	return (0);
}

int	ft_unset(char **cmd, t_env *env_list)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		delete_env_node(cmd[i], &env_list);
		i++;
	}
	return (0);
}
