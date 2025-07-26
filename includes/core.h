/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:37:28 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:42:06 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "types.h"

// Data

void	init_data(t_data *data, char *envp[]);
void	free_data(t_data *data);

// Pipeline

int		init_pipeline(t_pipeline *pipeline);
void	free_pipeline(t_pipeline *pipeline);

// Exit

void	perror_exit(char *error_message, int n_exit);
int		perror_return(char *error_message, int n_return);
int		print_error_return(char *error_message, int n_return);

#endif
