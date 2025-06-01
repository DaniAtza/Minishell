/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:18:11 by dagredan          #+#    #+#             */
/*   Updated: 2025/05/28 15:50:23 by dagredan         ###   ########.fr       */
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
	full_path = (char *) ft_calloc(size, sizeof(char));
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, size);
	ft_strlcat(full_path, "/", size);
	ft_strlcat(full_path, cmd_name, size);
	return (full_path);
}

static void	free_path_dirs(char **dirs)
{
	int	i;

	if (!dirs)
		return ;
	i = 0;
	while (dirs[i])
	{
		free(dirs[i]);
		i++;
	}
	free(dirs);
}

static char	**get_path_dirs(void)
{
	char	*path_env;
	char	**dirs;

	path_env = getenv("PATH");
	if (!path_env)
		path_env = DEF_PATH;
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	return (dirs);
}

char	*get_pathname(char *cmd_name)
{
	char	*pathname;
	char	**path_dirs;
	int		i;

	if (!cmd_name || !*cmd_name)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	path_dirs = get_path_dirs();
	if (!path_dirs)
		return (NULL);
	i = 0;
	while (path_dirs[i])
	{
		pathname = ft_pathjoin(path_dirs[i], cmd_name);
		if (!pathname)
			break ;
		if (access(pathname, F_OK) == 0)
			break ;
		free(pathname);
		pathname = NULL;
		i++;
	}
	free_path_dirs(path_dirs);
	return (pathname);
}
