/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:49:09 by datienza          #+#    #+#             */
/*   Updated: 2025/07/20 12:35:36 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_signal_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	postexecution_signal_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	heredoc_signal_handler(int signum)
{
	(void)signum;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(130);
}
