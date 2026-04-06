/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:04:43 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	unsigned long	i;

	i = 0;
	if (size == 0)
		return (0);
	while (s1[i] && s2[i] && i < size)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	if (!s1[i] && s2[i] && i == size)
		return (0);
	if (s1[i] == '\0' && s2[i] != '\0')
		return (-1);
	if (s2[i] == '\0' && s1[i] != '\0')
		return (1);
	return (0);
}

// #include<string.h>
// int main(void)
// {
// 	printf("%d\n", ft_strncmp("abcdef", "abcdefghijklmnop", 6));
// 	printf("%d\n", strncmp("abcdef", "abcdefghijklmnop", 6));
// 	return (0);
// }