/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:21:20 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/16 22:05:28 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Checks if a character is within ASCII range (0-127).
 * Returns 1 if character is ASCII, 0 otherwise.
 */
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
