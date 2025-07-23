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

static int	no_num(char *arg)
{
	int	i;

	i = 0;
	if(!arg)
		return(1);
	while(arg[i])
	{
		if(!ft_isdigit(arg[i]))
		{
			ft_putendl_fd("exit: ", STDERR_FILENO);
			ft_putendl_fd(arg, STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_exit(char **argv, t_data *data)
{

	if(!no_num(argv[1]))
	{
		data->last_exit_status = 2;
		return ;
	}
	
	
	
	
	//TODO de
	exit(data->last_exit_status);
}