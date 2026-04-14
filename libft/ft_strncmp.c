/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:16:04 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/24 16:20:01 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  strcmp()  function compares the two strings s1 and s2.  The locale
       is not taken into account (for  a  locale-aware  comparison,  see  str‐
       coll(3)).  The comparison is done using unsigned characters.

       strcmp() returns an integer indicating the result of the comparison, as
       follows:

       • 0, if the s1 and s2 are equal;

       • a negative value if s1 is less than s2;

       • a positive value if s1 is greater than s2.

       The strncmp() function is similar, except it compares  only  the  first
       (at most) n bytes of s1 and s2.
 * 
 * @param s1 This is the first string to be compared.
 * @param s2 This is the second string to be compared.
 * @param n This parameter refer to maximum number of characters to be compared.
 * @return int The strcmp() and strncmp() functions return an integer less 
 * than, equal to, or greater than zero if s1 (or the first n bytes thereof) 
 * is found, respectively, to be less than, to match, or be greater than s2.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*u_s1 = (const unsigned char	*)s1;
	const unsigned char	*u_s2 = (const unsigned char	*)s2;

	i = 0;
	while ((u_s1[i] || u_s2[i]) && (i < n))
	{
		if (u_s1[i] != u_s2[i])
			return (u_s1[i] - u_s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*s1 = "test\200";
	char	*s2 = "test\0";
	size_t	n = 6;

	printf("strncmp: %d\n\n",strncmp(s1, s2, n));

	printf("ft_strncmp: %d\n\n",ft_strncmp(s1, s2, n));
}*/