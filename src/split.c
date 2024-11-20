/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:32:47 by paranha           #+#    #+#             */
/*   Updated: 2024/05/16 14:44:30 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	process_quoted_segment(const char **str, char ***result,
		int *word_index, const char **word_start)
{
	char	*word;
	char	quote_type;

	quote_type = **str;
	*str += 1;
	*word_start = *str;
	while (**str && **str != quote_type)
		(*str)++;
	if (**str == quote_type)
	{
		word = extract_word(*word_start, *str);
		if (!word)
			exit(EXIT_FAILURE);
		(*str)++;
		*word_start = *str;
		(*result)[*word_index] = word;
		(*word_index)++;
	}
}

void	process_normal_word(const char **str, char ***result, int *word_index,
		const char **word_start)
{
	*word_start = *str;
	while (**str && !is_whitespace(**str) && **str != '"' && **str != '\'')
		(*str)++;
	(*result)[*word_index] = extract_word(*word_start, *str);
	if (!(*result)[*word_index])
		exit(EXIT_FAILURE);
	(*word_index)++;
}

char	**split_quoted_helper(const char *str, int num_words)
{
	char		**result;
	int			word_index;
	int			in_quotes;
	const char	*word_start;

	word_start = str;
	word_index = 0;
	in_quotes = 0;
	result = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*str)
	{
		if ((*str == '"' || *str == '\'') && !in_quotes)
			process_quoted_segment(&str, &result, &word_index, &word_start);
		else if (!is_whitespace(*str) && !in_quotes)
			process_normal_word(&str, &result, &word_index, &word_start);
		else
			str++;
	}
	result[word_index] = NULL;
	return (result);
}

char	**ft_split_quoted(const char *str)
{
	int		num_words;
	char	**result;

	num_words = count_words(str);
	result = split_quoted_helper(str, num_words);
	if (!result)
		return (NULL);
	return (result);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
