/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:28:31 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_chooseto_one(char car, va_list argptr)
{
	int	j;

	j = 0;
	if (car == 'c')
		j += c(va_arg(argptr, int));
	else if (car == 's')
		j += s(va_arg(argptr, char *));
	else if (car == 'p')
		j += p(va_arg(argptr, void *));
	else if (car == 'd' || car == 'i')
		j += d_i(va_arg(argptr, int));
	else if (car == 'u')
		j += u(va_arg(argptr, unsigned int));
	else if (car == 'x')
		j += x(va_arg(argptr, unsigned int));
	else if (car == 'X')
		j += upperx(va_arg(argptr, unsigned int));
	else if (car == '%')
	{
		write(1, "%", 1);
		j += 1;
	}
	return (j);
}

int	ft_printf(const char *core, ...)
{
	int		j;
	int		i;
	va_list	argptr;

	j = 0;
	i = 0;
	if (!core)
		return (-1);
	va_start(argptr, core);
	while (core[i])
	{
		if (core[i] != '%')
		{
			ft_putchar_fd(core[i], 1);
			j++;
		}
		else
			j += ft_chooseto_one(core[++i], argptr);
		i++;
	}
	va_end(argptr);
	return (j);
}

// int	main(void)
// {	
// 	ft_printf(NULL);
// 	return (0);
// }