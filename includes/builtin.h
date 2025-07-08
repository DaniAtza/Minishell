/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:33:18 by datienza          #+#    #+#             */
/*   Updated: 2025/07/04 22:18:43 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int		ft_echo(char **argv);
int		ft_pwd(char *current_pwd);
int		ft_export(char **argv, t_env *env_list);
int		ft_unset(char **argv, t_env *env_list);
int		ft_cd(char **argv, t_data *data);

char	*search_env(char *env_variable, t_env *env_list);
int		check_arg_error(char **argv);

int		is_builtin(char **argv);
int		exe_builtin(char **argv, t_data *data);

#endif
