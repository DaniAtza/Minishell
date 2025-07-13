/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:34:39 by datienza          #+#    #+#             */
/*   Updated: 2025/07/01 22:40:06 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

typedef struct s_signal_backup
{
	void	(*old_sigint)(int);
	void	(*old_sigquit)(int);
}	t_signal_backup;

void	        setup_signals(void);
void	        signal_handler(int signum);
void	        setup_child_signals(void);
void		    handle_child(int signum);
void			restore_signals(t_signal_backup backup);
t_signal_backup	set_execution_signals(void);

#endif