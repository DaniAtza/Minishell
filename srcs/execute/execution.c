/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:14:23 by datienza          #+#    #+#             */
/*   Updated: 2025/06/04 19:49:03 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child_process(t_process *process, int **pipes, t_env *env_list)
{
	setup_child_pipes(process, pipes);
	if (process->redirects && apply_redirects(process->redirects))
		exit(1);
	if (is_builtin(process->argv))
	{
		exe_builtin(process->argv, env_list);
		exit(0);
	}
	process->pathname = get_pathname(process->argv[0]);
	if (!process->pathname)
		cmd_not(process->argv[0]);
	execve(process->pathname, process->argv, NULL);
	error_exit(process->pathname, 1);
}

void	execute_processes(t_data *data, t_env *env_list)
{
	t_process	*current;

	current = data->processes;
	while (current)
	{
		current->pid = fork();
		if (current->pid == -1)
			error_exit("fork", 1);
		if (current->pid == 0)
			execute_child_process(current, data->pipes, env_list);
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
int	execute_pipeline(t_data *data, t_env *env_list)
{
	execute_processes(data, env_list);
	return (wait_processes(data));
}
