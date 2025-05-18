/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:32:56 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/16 22:06:57 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Applies a function to each character of a string,
 * passing both the character and its index as arguments,
 * and creating a new string with the results.
 * Returns the newly allocated string, or NULL if allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	new = (char *) ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
