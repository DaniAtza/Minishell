/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:14:23 by datienza          #+#    #+#             */
/*   Updated: 2025/07/13 20:25:11 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child_process(t_process *process, t_pipeline *pipeline, int **pipes, t_data *data)
{
	setup_child_signals();
	setup_child_pipes(process, pipes);
	if (apply_redirects(process->redirects) == -1)
		exit(1);
	if (!process->argv || !process->argv[0])
		exit(0);
	if (is_builtin(process->argv))
	{
		exe_builtin(process->argv, pipeline, data);
		exit(0);
	}
	process->pathname = get_pathname(process->argv[0], data->env_list);
	if (!process->pathname)
		cmd_not_found(process->argv[0]);
	execve(process->pathname, process->argv, NULL);
	error_exit(process->pathname, 1);
}

void	execute_processes(t_pipeline *pipeline, t_data *data)
{
	t_process	*current;

	current = pipeline->processes;
	while (current)
	{
		current->pid = fork();
		if (current->pid == -1)
		{
			perror("fork");
			return ;
		}
		if (current->pid == 0)
			execute_child_process(current, pipeline, pipeline->pipes, data);
		current = current->next;
	}
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

void	execute_pipeline(t_pipeline *pipeline, t_data *data)
{
	execute_processes(pipeline, data);
	setup_postexecution_signals();
	wait_processes(pipeline, data);
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
		data->last_exit_status = 0;
	}
	else
	{
		execute_pipeline(pipeline, data); // TODO: Check error
	}
}
