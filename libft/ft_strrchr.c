/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:16:23 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/20 19:01:58 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strrchr() function returns a pointer to the last occurrence of  the
       character c in the string s.
 * 
 * @param s This is the C string.
 * @param c This is the character to be located. It is passed as its int 
 * promotion, but it is internally converted back to char.
 * @return char* The strchr() and strrchr() functions return a pointer  
 * to  the  matched character  or NULL if the character is not found. 
 * The terminating null byte is considered part of the string, so that 
 * if  c  is  specified  as '\0', these functions return a pointer to 
 * the terminator.
 */
char	*ft_strrchr(const char *s, int c)
{
	char	c_char;
	int		i;

	i = ft_strlen(s);
	c_char = (char)c;
	while (i >= 0)
	{
		if (s[i] == c_char)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	int	c;
	char	*s = "\0";

	c = '\0';
	printf("strchr address: %p\n", strchr(s, c));
	printf("ft_strchr address: %p\n", ft_strchr(s, c));
}*/