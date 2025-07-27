/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:33:18 by datienza          #+#    #+#             */
/*   Updated: 2025/07/27 18:00:29 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void		ft_echo(char **argv, t_data *data);
int			ft_cd(char **argv, t_data *data);
void		ft_pwd(char *current_pwd, t_data *data);
int			ft_export(char **argv, t_env *env_list, t_data *data);
void		ft_unset(char **argv, t_env *env_list, t_data *data);
void		ft_exit(char **argv, t_pipeline *pipeline, t_data *data);

int			is_builtin(char **argv);
int			exe_builtin(char **argv, t_pipeline *pipeline, t_data *data);

#endif
