/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:11:59 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/24 16:17:42 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The  memmove()  function  copies n bytes from memory area src to memory
       area dest.  The memory areas may overlap: copying takes place as though
       the  bytes in src are first copied into a temporary array that does not
       overlap src or dest, and the bytes are then copied from  the  temporary
       array to dest.
 * @param dst This is a pointer for destination array where the content is to 
 * be copied. It is type-casted to a pointer of type void*.
 * @param src The is a second pointer that denote the source of data to be 
 * copied. It is also type-casted to a pointer of type void*.
 * @param len This parameter refer to number of bytes to be copied.
 * @return void* The memmove() function returns a pointer to dest.
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	const unsigned char	*u_src;
	unsigned char		*u_dst;

	u_src = (const unsigned char *)src;
	u_dst = (unsigned char *)dst;
	if (dst == src || len == 0)
		return (dst);
	i = 0;
	while (i < len)
	{
		if (u_dst < u_src)
		{
			u_dst[i] = u_src[i];
			i++;
		}
		else
		{
			len--;
			u_dst[len] = u_src[len];
		}
	}
	return (dst);
}

/*
int main(void)
{
    char	src[1] = "";
	
	char	src1[1] = "";

	memmove(src1, "Learning", 4);
	printf("%s\n", src1);

	ft_memmove(src, "Learning", 4);
	printf("%s\n", src);
}*/