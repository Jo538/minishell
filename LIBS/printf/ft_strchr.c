/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:51:18 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *str, int to_find)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((unsigned char *)str)[i] == to_find % 256)
			break ;
		i++;
	}
	if (((unsigned char *)str)[i] == to_find % 256)
		return (&((char *)str)[i]);
	return (NULL);
}

/*
#include<stdio.h>
int main(void)
{
	printf("%s \n" ,ft_strchr("test", '\0'));
	printf("%s \n" , strchr("test", '\0'));
	return (0);
}*/