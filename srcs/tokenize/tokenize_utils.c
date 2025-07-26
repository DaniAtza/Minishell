/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:44:07 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 17:59:04 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special(char c)
{
	return (is_operator(c) || is_blank(c) || c == '#');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
