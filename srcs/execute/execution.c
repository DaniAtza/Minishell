/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:14:23 by datienza          #+#    #+#             */
/*   Updated: 2025/08/01 19:57:42 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child_process(t_process *proc, t_pipeline *pline, t_data *data)
{
	int	error_num;

	setup_child_signals();
	setup_child_pipes(proc, pline->pipes);
	error_num = apply_redirects(proc->redirects);
	if (error_num == -1)
		exit(100);
	else if (error_num == 1)
		exit(1);
	if (!proc->argv || !proc->argv[0])
		exit(0);
	if (is_builtin(proc->argv))
	{
		if (exe_builtin(proc->argv, pline, data) == -1)
			exit (100);
		exit(0);
	}
	proc->pathname = get_pathname(proc->argv[0], data->env_list);
	if (!proc->pathname)
		cmd_not_found(proc->argv[0]);
	execve(proc->pathname, proc->argv, NULL); //TODO add env
	perror_exit(proc->pathname, 1); //TODO too many code error 2...
}

int	execute_processes(t_pipeline *pipeline, t_data *data)
{
	t_process	*current;

	current = pipeline->processes;
	while (current)
	{
		current->pid = fork();
		if (current->pid == -1)
		{
			perror("fork");
			return (-1);
		}
		if (current->pid == 0)
			execute_child_process(current, pipeline, data);
		current = current->next;
	}
	return (0);
}

void	wait_processes(t_pipeline *pipeline, t_data *data)
{
	t_process	*current;
	int			status;

	close_pipes(pipeline->pipes);
	current = pipeline->processes;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (!current->next)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
				data->last_exit_status = 128 + WTERMSIG(status);
			}
			else if (WIFEXITED(status))
				data->last_exit_status = WEXITSTATUS(status);
		}
		current = current->next;
	}
}

int	execute_pipeline(t_pipeline *pipeline, t_data *data)
{
	if (execute_processes(pipeline, data) == -1)
	{
		setup_postexecution_signals();
		return (-1);
	}
	setup_postexecution_signals();
	wait_processes(pipeline, data);
	if (data->last_exit_status == 100)
		return (-1);
	return (0);
}

void	handle_execution(t_pipeline *pipeline, t_data *data)
{
	if (pipeline->process_count == 1 && (is_builtin(pipeline->processes->argv)))
	{
		if (save_stdio_fds(pipeline->processes) == -1)
		{
			data->last_exit_status = 1;
			return ;
		}
		if (apply_redirects(pipeline->processes->redirects) == -1)
		{
			data->last_exit_status = 1;
			restore_stdio_fds(pipeline->processes);
			return ;
		}
		if (exe_builtin(pipeline->processes->argv, pipeline, data) == -1)
			data->last_exit_status = 1;
		restore_stdio_fds(pipeline->processes);
	}
	else
	{
		if (execute_pipeline(pipeline, data) == -1)
			data->last_exit_status = 1;
	}
}
