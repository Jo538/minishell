/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:59:45 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/24 11:07:36 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long n)
{
	int	div;

	div = 0;
	if (n < 0)
	{
		div++;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		div++;
	}
	return (div + 1);
}

char	*ft_itoa(int n)
{
	int		len;
	long	n_long;
	char	*ptr;

	n_long = n;
	len = ft_len(n_long);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		ptr[0] = '-';
		n_long = -n_long;
	}
	ptr[len] = '\0';
	len--;
	while (len > 0)
	{
		ptr[len] = (n_long % 10) + 48;
		n_long /= 10;
		len--;
	}
	if (ptr[0] != '-')
		ptr[len] = n_long + 48;
	return (ptr);
}
/*
int main(void)
{
	int n = 9;

	char *dst = ft_itoa(n);
	printf("%s\n", dst);
	free(dst);
	
}*/