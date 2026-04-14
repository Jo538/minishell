/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:22:42 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/26 14:50:22 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}
/*
int main(void)
{
	t_list node = {"Hola", NULL};
	t_list *lst = NULL;
	t_list new_node = {"Bonjour", NULL};
	t_list *new = &new_node;
	
	ft_lstadd_front(&lst, new);
	
	printf("Head: %s\n", (char *)(lst -> content));
	printf("Next: %s\n", (char *)(lst -> next -> content));
}*/