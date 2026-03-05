/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arr_sort(char **arr, int (*cmp)(void *, void *))
{
	int		i;
	int		j;
	char	*key;

	if (!arr || !cmp)
		return ;
	i = 1;
	while (arr[i])
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && cmp(arr[j], key) > 0)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		i++;
	}
}
