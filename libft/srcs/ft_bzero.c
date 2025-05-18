/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:08:09 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/16 22:05:18 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Fills a block of memory with zeros.
 * Returns nothing (void).
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
