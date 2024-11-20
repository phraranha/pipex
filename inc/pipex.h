/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:25:50 by paranha           #+#    #+#             */
/*   Updated: 2024/05/16 15:44:41 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

void	first_process(char *infile, char *cmd, char **envp, int *fd);
void	last_process(char *cmd, char *outfile, char **envp, int *fd);
void	print_usage_error(void);
int		main(int argc, char **argv, char **envp);
char	**get_paths_from_env(char **envp);
char	*find_path_var(char **envp);
char	*search_paths(char **paths, char *cmd);
void	execute_command(char *argv, char **envp);
void	exec_command(char *path, char **cmd, char **envp);
char	*find_command_path(char *cmd, char **envp);
int		open_input_file(char *file);
int		open_output_file(char *file);
int		count_words(const char *str);
char	*extract_word(const char *start, const char *end);
void	process_quoted_segment(const char **str, char ***result,
			int *word_index, const char **word_start);
void	process_normal_word(const char **str, char ***result, int *word_index,
			const char **word_start);
char	**split_quoted_helper(const char *str, int num_words);
char	**ft_split_quoted(const char *str);
void	free_split(char **split);
char	**parse_command(char *argv);
void	error(void);
void	close_in_out(void);
void	close_but_err(void);
int		is_whitespace(char c);
void	close_pipes(int *fd);

#endif
