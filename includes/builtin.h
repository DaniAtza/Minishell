/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: datienza <datienza@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:33:18 by datienza          #+#    #+#             */
/*   Updated: 2025/06/07 17:21:09 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int	ft_echo(char **arg);
int	ft_pwd(void);
int	ft_export(char **cmd, t_env **env_list);
int	ft_unset(char **cmd, t_env **env_list);
int	ft_cd(char **arg, t_env **env_list);

int	is_builtin(char **cmd);
int	exe_builtin(char **cmd, t_env *env_list);

#endif
