/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:37:28 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/04 22:18:50 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "types.h"

void 	init_gdata(t_gdata *gdata, char *envp[]);
int		init_data(t_data *data);
void	free_gdata(t_gdata *gdata);
void	free_data(t_data *data);

#endif

