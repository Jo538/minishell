/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:21:24 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/19 15:50:53 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief  The  strdup() function returns a pointer to a new string which 
 * is a duplicate of the string s.  Memory for the new string  is  
 * obtained  with malloc(3), and can be freed with free(3).
 * @param s1 The string to duplicate.
 * @return char* The pointer to the duplicated string.
 */
char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*copy;

	i = 0;
	len = ft_strlen(s1);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
/*
int main(void)
{
    char s1;
    s1 = NULL;

    chars2 = strdup(s1);
    printf("strdup: %s\n\n", s2);
    free(s2);

    char s3 = ft_strdup(s1);
    printf("ft_strdup: %s\n\n", s3);
    free(s3);
}*/
