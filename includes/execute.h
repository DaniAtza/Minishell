/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:59:29 by datienza          #+#    #+#             */
/*   Updated: 2025/07/26 18:14:36 by datienza         ###   ########.fr       */
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

void	execute_child_process(t_process *proc, t_pipeline *pline, t_data *data);
void	execute_processes(t_pipeline *pipeline, t_data *data);
void	wait_processes(t_pipeline *pipeline, t_data *data);
void	execute_pipeline(t_pipeline *pipeline, t_data *data);
void	handle_execution(t_pipeline *pipeline, t_data *data);
void	setup_child_pipes(t_process *proc, int **pipes);
int		apply_redirects(t_redirect *redir);

char	*get_pathname(char *cmd_name, t_env *env_list);
void	error_exit(char *error, int n_exit);

int		print_and_return_error(char *message, int return_value);
void	cmd_not_found(char *cmd);

int		save_stdio_fds(t_process *processes);
int		restore_stdio_fds(t_process *processes);

int		handle_heredocs(t_data *data, t_process *processes);
int		create_all_tmp_files(t_process *processes);

#endif
