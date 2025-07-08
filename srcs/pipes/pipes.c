/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:41:20 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/08 19:06:21 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**create_pipes(size_t count)
{
	int		**pipes;
	size_t	i;

	pipes = (int **)ft_calloc(count + 1, sizeof(int *));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipes[i] = (int *)ft_calloc(2, sizeof(int));
		if (!pipes[i])
		{
			destroy_pipes(&pipes);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			free(pipes[i]);
			pipes[i] = NULL;
			destroy_pipes(&pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	close_pipes(int **pipes)
{
	size_t	i;

	i = 0;
	while (pipes[i])
	{
		if (close(pipes[i][0]) == -1)
			perror("close");
		if (close(pipes[i][1]) == -1)
			perror("close");
		i++;
	}
}

void	free_pipes(int ***pipes_addr)
{
	int		**pipes;
	size_t	i;

	if (!*pipes_addr)
		return ;
	pipes = *pipes_addr;
	i = 0;
	while (pipes[i])
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	*pipes_addr = NULL;
}

void	destroy_pipes(int ***pipes_addr)
{
	close_pipes(*pipes_addr);
	free_pipes(pipes_addr);
}

void	assign_pipes_to_processes(int **pipes, t_pipeline *pipeline)
{
	t_process	*current;
	size_t		i;

	i = 0;
	current = pipeline->processes;
	while (current)
	{
		if (i < pipeline->process_count - 1)
			current->pipe_write_fd = pipes[i][1];
		else
			current->pipe_write_fd = -1;
		if (i > 0)
			current->pipe_read_fd = pipes[i - 1][0];
		else
			current->pipe_read_fd = -1;
		current = current->next;
		i++;
	}
}
