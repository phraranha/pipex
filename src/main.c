/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:33:40 by paranha           #+#    #+#             */
/*   Updated: 2024/05/16 15:44:08 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		print_usage_error();
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	else if (pid == 0)
	{
		close(fd[0]);
		first_process(argv[1], argv[2], envp, fd);
		exit(EXIT_SUCCESS);
	}
	last_process(argv[3], argv[4], envp, fd);
	close_pipes(fd);
	waitpid(pid, NULL, 0);
	return (0);
}

void	first_process(char *infile, char *cmd, char **envp, int *fd)
{
	int	infile_fd;

	if (infile)
	{
		infile_fd = open_input_file(infile);
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
	}
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execute_command(cmd, envp);
	free_split(&cmd);
}

void	last_process(char *cmd, char *outfile, char **envp, int *fd)
{
	int	outfile_fd;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	outfile_fd = open_output_file(outfile);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	execute_command(cmd, envp);
	free_split(&cmd);
}

int	open_input_file(char *file)
{
	int	infile;

	infile = open(file, O_RDONLY, 0644);
	if (infile < 0)
	{
		close_but_err();
		error();
	}
	return (infile);
}

int	open_output_file(char *file)
{
	int	outfile;

	outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile < 0)
	{
		close(STDIN_FILENO);
		error();
	}
	return (outfile);
}
