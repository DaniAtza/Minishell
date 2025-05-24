/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:23:00 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/22 19:23:03 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_token *token)
{
	return (token->type == VLINE);
}

int	is_redirection(t_token *token)
{
	return (token->type == LESS || token->type == GREAT
		|| token->type == DLESS || token->type == DGREAT);
}

int	is_word(t_token *token)
{
	return (token->type == WORD);
}
