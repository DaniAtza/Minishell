/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 16:13:48 by datienza          #+#    #+#             */
/*   Updated: 2025/05/17 14:08:26 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	tokenize_line(&data, argv[1]);
	free_tokens(&data);
	return (0);
}
