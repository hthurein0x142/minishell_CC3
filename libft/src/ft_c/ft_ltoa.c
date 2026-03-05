/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa(long n)
{
	char			buf[22];
	int				i;
	int				neg;
	unsigned long	num;

	i = 21;
	buf[i] = '\0';
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		num = -(unsigned long)n;
	}
	else
		num = (unsigned long)n;
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
