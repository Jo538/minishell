/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 07:56:18 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

extern int	ft_strlen(const char *str);

char	*ft_strdup(const char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*dest;

	j = 0;
	i = ft_strlen(src);
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	while (j < i)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/*
#include<stdio.h>
int	main(void)
{
	char    *str;

	str = ft_strdup("");
	printf("%s", str);
	free (str);
	return(0);
}
*/