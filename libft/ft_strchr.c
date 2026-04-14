/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:13:49 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/19 13:49:32 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  strchr() function returns a pointer to the first occurrence of the
       character c in the string s.
 * @param s It is the string in which we have to search the character. 
 * This string is a constant character pointer, meaning that the function 
 * will not modify the string.
 * @param c It is a character to be searched in the string. Though passed 
 * as an int, it represents a character and is cast internally. This allows 
 * strchr() to be used with character values, including special characters 
 * and ASCII values.
 * @return char* The strchr() and strrchr() functions return a pointer  
 * to  the  matched character  or NULL if the character is not found. 
 * The terminating null byte is considered part of the string, so that 
 * if  c  is  specified  as '\0', these functions return a pointer to 
 * the terminator.
 */
char	*ft_strchr(const char *s, int c)
{
	char	c_char;
	int		i;

	i = 0;
	c_char = (char)c;
	while (s[i])
	{
		if (s[i] == c_char)
			return ((char *)&s[i]);
		i++;
	}
	if (c_char == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
int	main(void)
{
	int	c;
	char	*s = "BONJOUR";

	c = '\0';
	printf("strchr address: %p\n", strchr(s, c));
	printf("ft_strchr address: %p\n", ft_strchr(s, c));
}*/