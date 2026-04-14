/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:53:37 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/24 13:11:02 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	n_long;
	long	mod;

	n_long = n;
	mod = 0;
	if (n_long < 0)
	{
		write(fd, "-", 1);
		n_long = -n_long;
	}
	if (n_long < 10)
	{
		n_long += 48;
		write(fd, &n_long, 1);
		return ;
	}
	if (n_long > 9)
	{
		mod = n_long % 10 + 48;
		ft_putnbr_fd(n_long / 10, fd);
		write(fd, &mod, 1);
	}
}
/*
int main(void)
{
	int n = -2147483648;
	int fd = 1;
	ft_putnbr_fd(n, fd);
}*/