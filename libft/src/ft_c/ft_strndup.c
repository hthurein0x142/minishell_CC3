/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhtun <thhtun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by thhtun            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by thhtun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s, len);
	copy[len] = '\0';
	return (copy);
}
