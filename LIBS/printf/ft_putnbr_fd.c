/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:25:18 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_putnbr_fd(int nb, int fd)
{
	int	tmp;

	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0 && nb != -2147483648)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb > 9 && nb != -2147483648)
		ft_putnbr_fd(nb / 10, fd);
	tmp = (nb % 10) + 48;
	write(fd, &tmp, 1);
}

/*
int main(void)
{
	ft_putnbr_fd(-2147483648, 1);
}
*/