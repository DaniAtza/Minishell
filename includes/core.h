/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:37:28 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:21:09 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "types.h"

// Data

void	init_data(t_data *data, char *envp[]);
void	free_data(t_data *data);

// Pipeline

int		init_pipeline(t_pipeline *pipeline);
void	free_pipeline(t_pipeline *pipeline);

#endif
