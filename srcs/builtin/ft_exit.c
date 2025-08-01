/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:21:58 by datienza          #+#    #+#             */
/*   Updated: 2025/07/26 18:19:09 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_number(char *arg)
{
	int	i;
	int	digit_len;

	i = 0;
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i] == '0')
		i++;
	digit_len = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
		digit_len++;
	}
	if (digit_len >= 19)
		return (0);
	return (1);
}

static int	convert_exit_num(char *arg)
{
	long long	num;
	int			exit_status;

	num = ft_atoll(arg);
	exit_status = (int)(num % 256);
	if (exit_status < 0)
		exit_status += 256;
	return (exit_status);
}

static void	no_numeric_arg(char *argv, size_t process_count, t_data *data)
{
	if (process_count == 1)
		printf("exit\n");
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	data->last_exit_status = 2;
}

static void	too_many_arg(size_t process_count, t_data *data)
{
	if (process_count == 1)
		printf("exit\n");
	ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
	data->last_exit_status = 1;
}

void	ft_exit(char **argv, t_pipeline *pipeline, t_data *data)
{
	int	exit_status;

	if (!argv[1])
	{
		if (pipeline->process_count == 1)
			printf("exit\n");
	}
	else if (!is_valid_number(argv[1]))
		no_numeric_arg(argv[1], pipeline->process_count, data);
	else if (argv[2])
	{
		too_many_arg(pipeline->process_count, data);
		return ;
	}
	else if (argv[1])
	{
		printf("exit\n");
		data->last_exit_status = convert_exit_num(argv[1]);
	}
	exit_status = data->last_exit_status;
	free_pipeline(pipeline);
	free_data(data);
	exit(exit_status);
}
