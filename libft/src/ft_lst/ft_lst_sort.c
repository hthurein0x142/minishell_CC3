/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhtun <thhtun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by thhtun            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by thhtun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*bubble_pass(t_list *lst, t_list *stop,
					int (*cmp)(void *, void *), int *swapped)
{
	void	*tmp;

	while (lst->next != stop)
	{
		if (cmp(lst->content, lst->next->content) > 0)
		{
			tmp = lst->content;
			lst->content = lst->next->content;
			lst->next->content = tmp;
			*swapped = 1;
		}
		lst = lst->next;
	}
	return (lst);
}

void	ft_lst_sort(t_list **lst, int (*cmp)(void *, void *))
{
	int		swapped;
	t_list	*stop;

	if (!lst || !*lst || !cmp)
		return ;
	stop = NULL;
	while (1)
	{
		swapped = 0;
		stop = bubble_pass(*lst, stop, cmp, &swapped);
		if (!swapped)
			break ;
	}
}
