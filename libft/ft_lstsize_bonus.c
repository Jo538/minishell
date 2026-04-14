/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:53:24 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/28 10:10:15 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* very interesting topic on compound literals!!! 
Main is what matters most with linked lists*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst -> next;
	}
	return (i);
}
/*
int	main(void)
{
	t_list	node3 = {(int[]){1, 2, 3}, NULL};
	t_list	node2 = {(int[]){4, 5, 6}, &node3};
	t_list	node1 = {(int[]){7, 8, 9}, &node2};
	t_list	node0 = {(int[]){10, 11, 12}, &node1};

	t_list	*lst = &node0;
	int n = ft_lstsize(lst);
	int i;
	while (lst)
	{
		i = 0;
		while (i < 3)
		{
			printf("%d, ", ((int *)lst -> content)[i]);
			i++;
		}
		printf("%c", '\n');
		lst = lst -> next;
	}
}*/