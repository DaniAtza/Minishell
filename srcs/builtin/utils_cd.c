/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:30:00 by datienza          #+#    #+#             */
/*   Updated: 2025/07/08 19:33:51 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg_error(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	if ((i - 1) == 0)
		return (0);
	else if ((i - 1) >= 2)
		return (ft_putendl_fd("cd: too many arguments", STDERR_FILENO), 1);
	return (0);
}
