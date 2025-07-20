/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:10:12 by datienza          #+#    #+#             */
/*   Updated: 2025/07/20 12:36:01 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, main_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_postexecution_signals(void)
{
	signal(SIGINT, postexecution_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, heredoc_signal_handler);
}
