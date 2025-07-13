/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:46:00 by datienza          #+#    #+#             */
/*   Updated: 2025/07/01 22:46:53 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	(void)signum;

	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_child(int signum)
{
	(void)signum;
}

t_signal_backup	set_execution_signals(void)
{
	t_signal_backup	backup;
	
	backup.old_sigint = signal(SIGINT, SIG_DFL);
	backup.old_sigquit = signal(SIGQUIT, handle_child);
	
	return (backup);
}

void	restore_signals(t_signal_backup backup)
{
	signal(SIGINT, backup.old_sigint);
	signal(SIGQUIT, backup.old_sigquit);
}