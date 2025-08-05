/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:18:11 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/03 10:43:41 by datienza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_pathjoin(char *dir, char *cmd_name)
{
	char	*full_path;
	size_t	size;

	if (!dir || !cmd_name)
		return (NULL);
	size = ft_strlen(dir) + ft_strlen("/") + ft_strlen(cmd_name) + 1;
	full_path = (char *)ft_calloc(size, sizeof(char));
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, size);
	ft_strlcat(full_path, "/", size);
	ft_strlcat(full_path, cmd_name, size);
	return (full_path);
}

static char	**get_path_dirs(t_env *env_list, int *flag)
{
	char	*path_env;
	char	**dirs;

	path_env = search_env("PATH", env_list);
	if (!path_env)
	{
		*flag = 1;
		return (NULL);
	}
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	return (dirs);
}

static int	search_in_path(char *cmd_name, t_env *env_list, t_process *proc)
{
	char	**path_dirs;
	int		i;
	int		flag;

	flag = 0;
	path_dirs = get_path_dirs(env_list, &flag);
	if (flag == 1)
		return (127);
	if (!path_dirs)
		return (perror_return("malloc", -1));
	i = 0;
	while (path_dirs[i])
	{
		proc->pathname = ft_pathjoin(path_dirs[i], cmd_name);
		if (!proc->pathname)
			break ;
		if (access(proc->pathname, F_OK) == 0)
			return (free_env_array(path_dirs), 0);
		free(proc->pathname);
		i++;
	}
	free_env_array(path_dirs);
	return (127);
}

int	get_pathname(char *cmd_name, t_env *env_list, t_process *proc)
{
	if (ft_strlen(cmd_name) == 0)
		return (127);
	if (ft_strchr(cmd_name, '/'))
	{
		proc->pathname = ft_strdup(cmd_name);
		return (0);
	}
	return (search_in_path(cmd_name, env_list, proc));
}
