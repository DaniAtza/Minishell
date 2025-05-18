/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:28:04 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/16 22:07:10 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Converts a lowercase letter to uppercase.
 * Returns uppercase letter if applicable, original character otherwise.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= ('a' - 'A'));
	return (c);
}
