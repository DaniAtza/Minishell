/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:31:59 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/16 22:07:09 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Converts an uppercase letter to lowercase.
 * Returns lowercase letter if applicable, original character otherwise.
 */
int	ft_tolower(int c)
{
	if ((c >= 'A' && c <= 'Z'))
		return (c += ('a' - 'A'));
	return (c);
}
