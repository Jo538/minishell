/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:02:47 by bribot            #+#    #+#             */
/*   Updated: 2026/02/16 07:54:31 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int n)
{
	if (n > 47 && n < 58)
		return (1);
	return (0);
}

static int	is_space(int n)
{
	if ((n >= 9 && n <= 13) || n == 32)
		return (1);
	return (0);
}

static int	is_only_space(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_space(s[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	j;
	int	sign;

	j = 0;
	i = 0;
	sign = 1;
	if (is_only_space(s))
		return (0);
	while (s[i] && is_space(s[i]))
		i++;
	if (s[i] && (s[i] == '-' || s[i] == '+'))
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		j = j * 10 + (s[i] - 48);
		i++;
	}
	return (j * sign);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d", ft_atoi(" etsttchasjvc145747  iheidgu"));
	return (0);
}
	*/
