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

int	execute_child_process(t_process *proc, t_pipeline *pline, t_data *data)
{
	int	return_value;

	setup_child_signals();
	if (setup_child_pipes(proc, pline->pipes) != 0)
		return (1);
	if (apply_redirects(proc->redirects) != 0)
		return (1);
	if (!proc->argv || !proc->argv[0])
		return (1);
	if (is_builtin(proc->argv))
	{
		if (exe_builtin(proc->argv, pline, data) != 0)
			return (1);
		return (0);
	}
	return_value = get_pathname(proc->argv[0], data->env_list, proc);
	if (return_value == 127)
		return (cmd_not_found(proc->argv[0]));
	else if (return_value != 0)
		return (1);
	data->exe_env = env_list_to_array(data->env_list);
	if (!data->exe_env)
		return (perror_return("malloc", 1));
	execve(proc->pathname, proc->argv, data->exe_env);
	return (perror_return_exec(proc->argv[0]));
}

int	execute_processes(t_pipeline *pipeline, t_data *data)
{
	t_process	*current;
	int			return_value;

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
		{
			return_value = execute_child_process(current, pipeline, data);
			free_pipeline(pipeline);
			free_data(data);
			exit(return_value);
		}
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
