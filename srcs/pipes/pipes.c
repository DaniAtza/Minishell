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

static int	*create_pipe(void)
{
	int		*new_pipe;

	new_pipe = (int *)ft_calloc(2, sizeof(int));
	if (!new_pipe)
	{
		perror("create_pipe: malloc");
		return (NULL);
	}
	if (pipe(new_pipe) == -1)
	{
		perror("create_pipe: pipe");
		free(new_pipe);
		return (NULL);
	}
	return (new_pipe);
}

int	**create_pipes(size_t count)
{
	int		**pipes;
	size_t	i;

	pipes = (int **)ft_calloc(count + 1, sizeof(int *));
	if (!pipes)
	{
		perror("create_pipes: malloc");
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		pipes[i] = create_pipe();
		if (!pipes[i])
		{
			close_pipes(pipes);
			free_pipes(&pipes);
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
		close(pipes[i][0]);
		close(pipes[i][1]);
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
