/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:20:39 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 19:05:43 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

// Pipes

int		**create_pipes(size_t count);
void	close_pipes(int **pipes);
void	free_pipes(int ***pipes_addr);
void	assign_pipes_to_processes(int **pipes, t_pipeline *pipeline);

#endif
