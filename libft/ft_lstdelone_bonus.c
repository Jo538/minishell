/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:06:51 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/28 10:08:48 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del(void *content)
{
	if (!content)
		return ;
	free(content);
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst -> content);
}
/*
int    main(void)
{
    t_list node1 = {"Guapa", NULL};

    t_list node2;
    node2.content = malloc(5 * sizeof(char));
    ft_memcpy(node2.content, "", 1);
    node1.next = &node2;

    t_list lst = &node1;

    ft_lstdelone(node1.next, del);

    while (lst -> next)
    {
        printf("%s\n", (char)lst -> content);
        lst = lst -> next;
    }
    printf("%p\n", lst -> content);
}*/