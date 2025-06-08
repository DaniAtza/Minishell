/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:59:29 by datienza          #+#    #+#             */
/*   Updated: 2025/06/07 17:21:57 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define DEF_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>

int		execute_pipeline(t_data *data);
void	execute_processes(t_data *data);
int		wait_processes(t_data *data);
void	setup_child_pipes(t_process *proc, int **pipes);
void	apply_redirects(t_redirect *redir);
char	*get_pathname(char *cmd_name);
void	error_exit(char *error, int n_exit);
int		print_and_return_error(char *message, int return_value);
int		cmd_not(char *cmd);
void	write_heredoc(int fd, char *delimiter);
void	apply_heredoc(t_redirect *redir);

#endif
