/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:37:30 by datienza          #+#    #+#             */
/*   Updated: 2025/07/07 20:05:41 by dagredan         ###   ########.fr       */
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

static int	check_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] && is_flag(argv[i]))
	{
		if (!is_flag(argv[i]))
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(char **argv)
{
	int	i;
	int	flag;

	if (!argv)
		return (1);
	i = 1;
	flag = 0;
	i += check_argv(argv + 1);
	if (i > 1)
		flag = 1;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
