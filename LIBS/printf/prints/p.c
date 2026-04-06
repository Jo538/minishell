/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:02:19 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	p(void *pointer)
{
	int					k;
	unsigned long int	p;

	p = (unsigned long int)pointer;
	if (!pointer)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write (1, "0x", 2);
	k = x(p);
	return (k + 2);
}

// int main(void)
// {
// 	printf("%d \n", p("554"));
// 	printf("%d \n",printf("%p", "554"));
// 	return(0);
// }