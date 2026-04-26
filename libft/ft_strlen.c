/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:52:56 by jchartie          #+#    #+#             */
/*   Updated: 2026/04/26 14:20:56 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strlen() function calculates the length of the string pointed to by
       s, excluding the terminating null byte ('\0').
 * 
 * @param s 
 * @return size_t  The strlen() function returns the number of bytes in the 
 * string pointed to by s.
 */
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
/*
int	main(int argc, char **argv)
{
	(void)argc;

	printf("ft_strlen: %d\n", ft_strlen(argv[1]));
	printf("strlen: %lu\n", strlen(argv[1]));
}*/
