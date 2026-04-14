/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:15:27 by jchartie          #+#    #+#             */
/*   Updated: 2026/03/02 16:20:18 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The strlcpy() and strlcat() functions copy and concatenate 
 * strings, stopping when either a NUL terminator in the source string 
 * is encountered or the specified full size of the destination buffer 
 * is reached. They NUL terminate the result if there is room. The 
 * application should ensure that room for the NUL terminator is included 
 * in dstsize.
 * 
 * The strlcpy() function shall copy not more than dstsize - 1 bytes 
 * from the string pointed to by src to the array pointed to by dst; 
 * a NUL byte in src and bytes that follow it shall not be copied. A 
 * terminating NUL byte shall be appended to the result, unless dstsize 
 * is 0. If copying takes place between objects that overlap, the behavior 
 * is undefined.
 * @param dst 
 * @param src 
 * @param dstsize 
 * @return size_t Upon successful completion, the strlcpy() function shall 
 * return the length of the string pointed to by src; that is, the number 
 * of bytes in the string, not including the terminating NUL byte.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	i;

	i = 0;
	n = ft_strlen((char *)src);
	if (dstsize != 0 && src)
	{
		while (src[i] && ((i + 1) < dstsize))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (n);
}
/*
int	main(void)
{
	char	*src = NULL;
	char	dst[5] = "";
	size_t	dstsize = 5;

	printf("strlcpy, size of src: %zu\n", strlcpy(dst, src, dstsize));
	printf("strlcpy, dst: %s\n\n", dst);

	ft_memset(dst, 0, 0);

	printf("cleaned dst: %s\n\n", dst);
	printf("ft_strlcpy, size of src: %zu\n", ft_strlcpy(dst, src, dstsize));
	printf("ft_strlcpy, dst: %s\n\n", dst);
}*/