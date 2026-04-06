/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:02:17 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int to_find)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (((unsigned char *)str)[i] == to_find % 256)
			return (&str[i]);
		i--;
	}
	return (NULL);
}

/*
#include<stdio.h>
int main(void)
{
	printf("%s" ,ft_strrchr("TEse", 't'));
	return (0);
}
*/