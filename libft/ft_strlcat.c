/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:14:51 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/21 11:02:56 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief The strlcpy() and strlcat() functions copy and concatenate 
 * strings, stopping when either a NUL terminator in the source string 
 * is encountered or the specified full size of the destination buffer 
 * is reached. They NUL terminate the result if there is room. The 
 * application should ensure that room for the NUL terminator is included 
 * in dstsize. The strlcat() function shall append not more than 
 * dstsize - strlen(dst) - 1 bytes from the string pointed to by src to 
 * the end of the string pointed to by dst; a NUL byte in src and bytes 
 * that follow it shall not be appended. The initial byte of src shall 
 * overwrite the NUL byte at the end of dst. A terminating NUL byte 
 * shall be appended to the result, unless its location would be at or 
 * beyond dst + dstsize. If copying takes place between objects that 
 * overlap, the behavior is undefined.
 * @param dst 
 * @param src 
 * @param dstsize 
 * @return size_t Upon successful completion, the strlcat() function 
 * shall return the initial length of the string (if any) pointed to 
 * by dst, as limited by dstsize, plus the length of the string pointed 
 * to by src; that is, the value that would be returned by 
 * strnlen(dst, dstsize) + strlen(src) before the strlcat() call.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	n;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	n = ft_strlen(dst);
	j = ft_strlen(src);
	if (dstsize <= n)
		return (dstsize + j);
	if (j > (dstsize - n - 1))
		k = dstsize - n - 1;
	else
		k = j;
	while (i < k)
	{
			dst[n + i] = src[i];
			i++;
	}
	dst[n + i] = '\0';
	return (n + j);
}
/*
int	main(void)
{
	const char	*src = "World";
	char		dst[20] = "Hello";
	unsigned int	dstsize = 3;

	printf("length src + dst = %lu\n", strlcat(dst, src, dstsize));
	printf("strlcat dst = %s\n", dst);


	memset(dst + 5, 0, dstsize - 5);
	printf("dst cleaned: %s\n", dst);

	ft_strlcat(dst, src, dstsize);
	printf("length src + dst = %lu\n", strlcat(dst, src, dstsize));
	printf("ft_strlcat dst = %s\n", dst);
}*/
