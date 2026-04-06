/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:46:46 by bribot            #+#    #+#             */
/*   Updated: 2026/02/16 09:48:08 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(long int n)
{
	if (n > 47 && n < 58)
		return (1);
	return (0);
}

static int	is_space(long int n)
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

long int	ft_atol(const char *s)
{
	long int	i;
	long int	j;
	long int	sign;

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
