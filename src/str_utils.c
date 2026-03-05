/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_strjoin3(const char *a, const char *b, const char *c)
{
	char	*res;
	size_t	la;
	size_t	lb;
	size_t	lc;

	la = ft_strlen(a);
	lb = ft_strlen(b);
	lc = ft_strlen(c);
	res = malloc(la + lb + lc + 1);
	if (!res)
		return (NULL);
	memcpy(res, a, la);
	memcpy(res + la, b, lb);
	memcpy(res + la + lb, c, lc);
	res[la + lb + lc] = '\0';
	return (res);
}

long long	ft_atoll(const char *s)
{
	long long	n;
	int			sign;

	n = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	return (n * sign);
}
