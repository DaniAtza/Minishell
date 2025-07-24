/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:21:58 by datienza          #+#    #+#             */
/*   Updated: 2025/07/18 19:24:37 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_number(char *arg)
{
	int	i = 0;
	
	if (!arg)
	{
		printf("exit\n");
		return (1);
	}
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	convert_exit_num(char *arg)
{
	long long	num;
	int			exit_status;

	num = atoll(arg); //TODO
	exit_status = (int)(num % 256);
	if (exit_status < 0)
		exit_status += 256;
	return (exit_status);
}

void	ft_exit(char **argv, t_data *data)
{
	int	exit_status;


	if(!is_valid_number(argv[1]))
	{
		printf("exit\n");  // if is father
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		data->last_exit_status = 2;
	}
	else if(argv[2])
	{
		printf("exit\n");  // if is father
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		data->last_exit_status = 1;
		return ;
	}
	if(argv[1])
	{
		printf("exit\n");
		data->last_exit_status = convert_exit_num(argv[1]);
	}
	exit_status = data->last_exit_status;
	//TODO free
	exit(exit_status);
}