/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:33:18 by datienza          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/26 18:12:53 by datienza         ###   ########.fr       */
=======
/*   Updated: 2025/07/26 19:08:48 by dagredan         ###   ########.fr       */
>>>>>>> 262ac74 (refactor: Update ft_cd.c and remove utils_cd.c)
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int		ft_echo(char **argv);
int		ft_cd(char **argv, t_data *data);
int		ft_pwd(char *current_pwd);
int		ft_export(char **argv, t_env *env_list);
int		ft_unset(char **argv, t_env *env_list);
void	ft_exit(char **argv, t_pipeline *pipeline, t_data *data);

int		is_builtin(char **argv);
int		exe_builtin(char **argv, t_pipeline *pipeline, t_data *data);

#endif
