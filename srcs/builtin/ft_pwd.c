/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 21:59:34 by datienza          #+#    #+#             */
/*   Updated: 2025/06/22 12:14:37 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*directory;//TTODO pwd delete

	directory = getcwd(NULL, 0);
	printf("%s\n", directory);
	free(directory);
	return (0);
}
