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


int	ft_cd(char **arg)
{

	if (check_arg_error(arg))
		return (1);
	
	if (!arg[1] || !(ft_strcmp(arg[1], "~")))
	{
		if (chdir("/home") == -1)
			return (1);
	}
	return (0);
}