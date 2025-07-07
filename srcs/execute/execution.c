/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:14:23 by datienza          #+#    #+#             */
/*   Updated: 2025/07/07 19:58:33 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child_process(t_process *process, int **pipes, t_gdata *gdata)
{
	setup_child_pipes(process, pipes);
	if (process->redirects && apply_redirects(process->redirects))
		exit(1);
	if (is_builtin(process->argv))
	{
		exe_builtin(process->argv, gdata);
		exit(0);
	}
	process->pathname = get_pathname(process->argv[0]);
	if (!process->pathname)
		cmd_not_found(process->argv[0]);
	execve(process->pathname, process->argv, NULL);
	error_exit(process->pathname, 1);
}

void	execute_processes(t_data *data, t_gdata *gdata)
{
	t_process	*current;

	current = data->processes;
	while (current)
	{
		current->pid = fork();
		if (current->pid == -1)
			error_exit("fork", 1);
		if (current->pid == 0)
			execute_child_process(current, data->pipes, gdata);
		current = current->next;
	}
}

int	wait_processes(t_data *data)
{
	t_process	*current;
	int			status;

	close_pipes(data->pipes);
	current = data->processes;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		current = current->next;
	}
	return (status);
}

//TODO CORRECT RETURN NUM
int	execute_pipeline(t_data *data, t_gdata *gdata)
{
	execute_processes(data, gdata);
	return (wait_processes(data));
}

void	handle_execution(t_data *data, t_gdata *gdata)
{
	if (data->processes_count == 1 && (is_builtin(&data->processes->argv[0])))
	{
		if (save_stdio_fds(data->processes) == -1)
			return ;
		if (apply_redirects(data->processes->redirects) == -1)
		{
			restore_stdio_fds(data->processes);
			return ;
		}
		exe_builtin(data->processes->argv, gdata);
		restore_stdio_fds(data->processes);
	}
	else
	{
		execute_pipeline(data, gdata); // TODO: Check error
	}
}
