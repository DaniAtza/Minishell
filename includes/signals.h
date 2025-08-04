/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:34:39 by datienza          #+#    #+#             */
/*   Updated: 2025/08/04 19:11:35 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

typedef struct s_signal_backup
{
	void	(*old_sigint)(int);
	void	(*old_sigquit)(int);
}	t_signal_backup;

t_signal_backup		set_execution_signals(void);
void				restore_signals(t_signal_backup backup);

int					setup_signals(void);
int					setup_postexecution_signals(void);
void				main_signal_handler(int signum);
void				postexecution_signal_handler(int signum);

void				setup_child_signals(void);

int					setup_heredoc_signals(void);
void				heredoc_signal_handler(int signum);

#endif
