/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	buf[12];
	int		i;
	int		neg;
	long	num;

	num = n;
	i = 11;
	buf[i] = '\0';
	neg = 0;
	if (num < 0)
	{
		neg = 1;
		num = -num;
	}
	if (num == 0)
		buf[--i] = '0';
	while (num > 0)
	{
		buf[--i] = '0' + (num % 10);
		num /= 10;
	}
	if (neg)
		buf[--i] = '-';
	return (ft_strdup(buf + i));
}
