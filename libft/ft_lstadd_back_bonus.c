/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:04:41 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/28 10:29:23 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	head = *lst;
	lst = &head;
	while (head -> next)
		head = head -> next;
	head -> next = new;
}
/*
int main(void)
{
    t_list    node1 = {"ipsum", NULL};
    t_list node0 = {"lorem", &node1};
    t_list new_node = {"dolor", NULL};

    t_list *lst = NULL;

    ft_lstadd_back(&lst, &new_node);

    while (lst -> next)
    {
        printf("%s: , address: %p\n", (char *)lst -> content, lst -> next);
        lst = lst -> next;
    }
    printf("%s: , address: %p\n", (char *)lst -> content, lst);
}*/