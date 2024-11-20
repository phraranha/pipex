/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:50:35 by paranha           #+#    #+#             */
/*   Updated: 2024/05/16 15:44:23 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	**parse_command(char *argv)
{
	char	**cmd;

	cmd = ft_split_quoted(argv);
	if (!cmd)
		error();
	return (cmd);
}

void	execute_command(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = parse_command(argv);
	if (!cmd[0] || !cmd[0][0])
	{
		free_split(cmd);
		perror("Empty command");
		close_in_out();
	}
	path = find_command_path(cmd[0], envp);
	if (path)
	{
		exec_command(path, cmd, envp);
		free_split(cmd);
		free(path);
	}
	else
	{
		free_split(cmd);
		free(path);
		perror("Command not found");
		close_in_out();
	}
}

void	exec_command(char *path, char **cmd, char **envp)
{
	if (execve(path, cmd, envp) == -1)
	{
		free_split(cmd);
		free(path);
		close_but_err();
		perror("Execution failed");
		exit(126);
	}
}
