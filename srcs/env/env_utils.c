/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:35:06 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/05 15:32:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_list(t_env *env_list, t_data *data)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	data->last_exit_status = 0;
}

void	print_env_list_export(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
}

char	*create_pwd_var(void)
{
	char	*pwd;
	char	*pwd_var;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("/");
	if (!pwd)
		return (NULL);
	pwd_var = ft_strjoin("PWD=", pwd);
	free(pwd);
	return (pwd_var);
}
