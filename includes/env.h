/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:51:54 by dagredan          #+#    #+#             */
/*   Updated: 2025/07/08 19:33:49 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	struct s_env	*next;
	char			*name;	
	char			*value;
}	t_env;

/* env_node.c */
t_env	*create_env_node(char *env_variable);
void	free_env_node(t_env **node_addr);

/* env_list.c */
t_env	*create_env_list(char *envp[]);
void	free_env_list(t_env **env_list_addr);
char	*search_env(char *name, t_env *env_list);
int		update_env_node(char *env_variable, t_env **env_list_addr);
void	delete_env_node(char *name, t_env **env_list_addr);

/* env_print.c */
void	print_env_list(t_env *env_list);
void	print_env_list_export(t_env *env_list);

#endif
