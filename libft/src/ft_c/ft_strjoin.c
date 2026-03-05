/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_total_len(size_t count, va_list args)
{
	size_t		total;
	size_t		i;
	const char	*s;

	total = 0;
	i = 0;
	while (i++ < count)
	{
		s = va_arg(args, const char *);
		if (s)
			total += ft_strlen(s);
	}
	return (total);
}

static void	fill_result(char *ptr, size_t count, va_list args)
{
	size_t		i;
	const char	*s;

	i = 0;
	while (i++ < count)
	{
		s = va_arg(args, const char *);
		if (s)
		{
			ft_memcpy(ptr, s, ft_strlen(s));
			ptr += ft_strlen(s);
		}
	}
	*ptr = '\0';
}

char	*ft_strjoin(size_t count, ...)
{
	va_list	args;
	va_list	args_copy;
	char	*result;

	va_start(args, count);
	va_copy(args_copy, args);
	result = (char *)malloc(get_total_len(count, args) + 1);
	va_end(args);
	if (!result)
	{
		va_end(args_copy);
		return (NULL);
	}
	fill_result(result, count, args_copy);
	va_end(args_copy);
	return (result);
}
