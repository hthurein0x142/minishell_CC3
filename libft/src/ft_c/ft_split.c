/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static void	free_arr(char **arr, int i)
{
	while (i > 0)
		free(arr[--i]);
	free(arr);
}

static int	fill_words(char **arr, const char *s, char c, int words)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	end = 0;
	while (i < words)
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] && s[end] != c)
			end++;
		arr[i] = ft_substr(s, start, end - start);
		if (!arr[i])
		{
			free_arr(arr, i);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	if (!fill_words(arr, s, c, words))
		return (NULL);
	arr[words] = NULL;
	return (arr);
}
