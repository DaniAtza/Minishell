/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:44:55 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:59:53 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*create_process(void)
{
	t_process	*new_process;

	new_process = (t_process *)ft_calloc(1, sizeof(t_process));
	if (!new_process)
		return (NULL);
	return (new_process);
}

void	append_process(t_process *new_process, t_process **processes)
{
	t_process	*current;

	if (!*processes)
		*processes = new_process;
	else
	{
		current = *processes;
		while (current->next)
			current = current->next;
		current->next = new_process;
	}
}

void	free_processes(t_process **processes)
{
	t_process	*current;
	t_process	*next;

	if (!*processes)
		return ;
	current = *processes;
	while (current)
	{
		next = current->next;
		if(current->pipe_read_fd > 0)
			close(current->pipe_read_fd);
		if(current->pipe_read_fd > 0)
			close(current->pipe_write_fd);
		if (current->redirects)
			free_redirects(&current->redirects);
		if (current->argv)
			free_argv(&current->argv);
		free(current);
		current = next;
	}
	*processes = NULL;
}

size_t	count_processes(t_process *processes)
{
	size_t		count;
	t_process	*current;

	count = 0;
	if (!processes)
		return (0);
	current = processes;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
