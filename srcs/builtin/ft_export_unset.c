/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:47:18 by datienza          #+#    #+#             */
/*   Updated: 2025/07/08 19:44:32 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export_error(char *arg)
{
	char	*error1;
	char	*error2;

	error1 = ft_strjoin("export: `", arg);
	if (!error1)
		return (-1);
	error2 = ft_strjoin(error1, "': not a valid identifier");
	free(error1);
	if (!error2)
		return (-1);
	ft_putendl_fd(error2, STDERR_FILENO);
	free(error2);
	return (-2);
}

static int	validate_variable_name(char *arg)
{
	size_t	i;

	i = 1;
	if (!is_valid_name_first_char(arg[0]))
		return (print_export_error(arg));
	while (arg[i] && arg[i] != '=')
	{
		if (!is_valid_name_char(arg[i]))
			return (print_export_error(arg));
		i++;
	}
	return (0);
}

int	ft_export(char **argv, t_env *env_list, t_data *data)
{
	size_t	i;
	int		error_num;
	size_t	flag;

	flag = 0;
	if (!argv[1])
		print_env_list_export(env_list);
	i = 1;
	while (argv[i])
	{
		error_num = validate_variable_name(argv[i]);
		if (error_num == 0)
			update_env_node(argv[i], &env_list);
		else if (error_num == -1)
			return (-1);
		else if (error_num == -2 && flag == 0)
			flag = 1;
		i++;
	}
	if (flag == 1)
		data->last_exit_status = 1;
	else
		data->last_exit_status = 0;
	return (0);
}

void	ft_unset(char **argv, t_env *env_list, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		delete_env_node(argv[i], &env_list);
		i++;
	}
	data->last_exit_status = 0;
}
