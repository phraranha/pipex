/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:39:02 by paranha           #+#    #+#             */
/*   Updated: 2024/05/16 13:36:23 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	close_pipes(int *fd)
{
	if (!fd)
		return ;
	close(fd[0]);
	close(fd[1]);
}

void	print_usage_error(void)
{
	ft_putstr_fd("Try: ./pipex \"infile\" \"cmd1\" \"cmd2\" \"outfile\"\n", 2);
	exit(EXIT_FAILURE);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	close_in_out(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(127);
}

void	close_but_err(void)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(3);
	close(4);
}
