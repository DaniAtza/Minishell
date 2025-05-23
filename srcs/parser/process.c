/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:44:55 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/23 11:52:19 by dagredan         ###   ########.fr       */
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
		if (current->redirects)
			free_redirects(&current->redirects);
		if (current->argv)
			free(current->argv);
		free(current);
		current = next;
	}
	*processes = NULL;
}
