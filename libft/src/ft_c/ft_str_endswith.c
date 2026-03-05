/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_endswith.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_endswith(const char *str, const char *suffix)
{
	size_t	slen;
	size_t	sfxlen;

	if (!str || !suffix)
		return (0);
	slen = ft_strlen(str);
	sfxlen = ft_strlen(suffix);
	if (sfxlen > slen)
		return (0);
	return (ft_strcmp(str + slen - sfxlen, suffix) == 0);
}
