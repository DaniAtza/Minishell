/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:51:54 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/26 18:07:21 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "types.h"

// Env node

t_env	*create_env_node(char *env_variable);
void	free_env_node(t_env **node_addr);

// Env list

t_env	*create_env_list(char *envp[]);
void	free_env_list(t_env **env_list_addr);
int		update_env_node(char *env_variable, t_env **env_list_addr);
void	delete_env_node(char *name, t_env **env_list_addr);
char	*search_env(char *name, t_env *env_list);

// Env utils

void	print_env_list(t_env *env_list, t_data *data);
void	print_env_list_export(t_env *env_list);

#endif
