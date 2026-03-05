/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_removeif.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by marvin            #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_removeif(t_list **lst, void (*del)(void *),
		int (*match)(void *, void *), void *ctx)
{
	t_list	*curr;
	t_list	*prev;
	t_list	*next;

	if (!lst || !match)
		return ;
	prev = NULL;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		if (match(curr->content, ctx))
		{
			if (prev)
				prev->next = next;
			else
				*lst = next;
			ft_lstdelone(curr, del);
		}
		else
			prev = curr;
		curr = next;
	}
}
