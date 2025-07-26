/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:37:43 by datienza          #+#    #+#             */
/*   Updated: 2025/07/26 18:42:21 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_exit(char *error_message, int n_exit)
{
	perror(error_message);
	exit(n_exit);
}

int	perror_return(char *error_message, int n_return)
{
	perror(error_message);
	return (n_return);
}

int	print_error_return(char *error_message, int n_return)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	return (n_return);
}
