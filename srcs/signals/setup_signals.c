/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:10:12 by datienza          #+#    #+#             */
/*   Updated: 2025/08/04 19:03:45 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_signals(void)
{
	if (signal(SIGINT, main_signal_handler) == SIG_ERR)
		return (-1);
	if (signal(SIGQUIT, SIG_IGN))
		return (-1);
	return (0);
}

int	setup_postexecution_signals(void)
{
	if (signal(SIGINT, postexecution_signal_handler) == SIG_ERR)
		return (-1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (-1);
	return (0);
}

int	setup_heredoc_signals(void)
{
	if (signal(SIGINT, heredoc_signal_handler) == SIG_ERR)
		return (-1);
	return (0);
}
