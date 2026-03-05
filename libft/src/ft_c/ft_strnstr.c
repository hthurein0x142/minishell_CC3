/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhtun <thhtun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by thhtun            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by thhtun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	size_t	i;

	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i + nlen <= len)
	{
		if (ft_strncmp(haystack + i, needle, nlen) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
