/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:37:30 by datienza          #+#    #+#             */
/*   Updated: 2025/05/29 21:42:16 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag(char *arg)
{
	int	i;

	if (ft_strncmp(arg, "-n", 2))
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] && is_flag(arg[i]))
	{
		if (!is_flag(arg[i]))
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(char **arg)
{
	int	i;
	int	flag;

	if (!arg)
		return (1);
	i = 1;
	flag = 0;
	i += check_arg(arg + 1);
	if (i > 1)
		flag = 1;
	while (arg[i])
	{
		printf("%s ", arg[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
