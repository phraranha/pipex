/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:49:50 by paranha           #+#    #+#             */
/*   Updated: 2024/05/16 14:28:46 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*find_path_var(char **envp)
{
	int		i;
	char	*path_var;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_var = ft_strdup(envp[i]);
			if (!path_var)
				return (NULL);
			return (path_var);
		}
		i++;
	}
	return (NULL);
}

char	**get_paths_from_env(char **envp)
{
	char	*path_var;
	char	**paths;

	path_var = find_path_var(envp);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var + 5, ':');
	if (!paths)
		return (NULL);
	free(path_var);
	return (paths);
}

char	*search_paths(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_paths_from_env(envp);
	path = search_paths(paths, cmd);
	free_split(paths);
	return (path);
}
