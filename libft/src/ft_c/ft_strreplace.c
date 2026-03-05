/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhtun <thhtun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by thhtun            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by thhtun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(const char *str, const char *old, const char *rep)
{
	char	*pos;
	char	*result;
	char	*tmp;

	if (!str || !old || !rep)
	{
		if (str)
			return (ft_strdup(str));
		return (ft_strdup(""));
	}
	pos = ft_strnstr(str, old, ft_strlen(str));
	if (!pos)
		return (ft_strdup(str));
	tmp = ft_substr(str, 0, pos - str);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(2, tmp, rep);
	free(tmp);
	if (!result)
		return (NULL);
	tmp = result;
	result = ft_strjoin(2, tmp, pos + ft_strlen(old));
	free(tmp);
	return (result);
}
