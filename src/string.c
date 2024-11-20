/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paranha <paranha@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:53:23 by paranha           #+#    #+#             */
/*   Updated: 2024/05/16 12:42:42 by phraranha        ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	count_words(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (!is_whitespace(*str) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_whitespace(*str))
			in_word = 0;
		str++;
	}
	return (count);
}

char	*extract_word(const char *start, const char *end)
{
	int		length;
	char	*word;
	int		i;

	i = 0;
	length = end - start;
	word = (char *)malloc((length + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < length)
	{
		word[i] = start[i];
		i++;
	}
	word[length] = '\0';
	return (word);
}
