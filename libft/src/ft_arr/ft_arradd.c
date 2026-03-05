/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	copy_old(char **new_arr, char **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			ft_arrfree(new_arr);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_arradd(char **arr, char *new_str)
{
	char	**new_arr;
	int		len;

	len = ft_arrlen(arr);
	new_arr = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!new_arr)
		return (NULL);
	if (!copy_old(new_arr, arr, len))
		return (NULL);
	new_arr[len] = ft_strdup(new_str);
	if (!new_arr[len])
	{
		ft_arrfree(new_arr);
		return (NULL);
	}
	new_arr[len + 1] = NULL;
	ft_arrfree(arr);
	return (new_arr);
}
