/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:55:19 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<stdio.h>
#include <limits.h>

static int	ft_count_len(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static	void	attrib_intmin(char *dest)
{
	dest[0] = '-';
	dest[1] = '2';
	dest[2] = '1';
	dest[3] = '4';
	dest[4] = '7';
	dest[5] = '4';
	dest[6] = '8';
	dest[7] = '3';
	dest[8] = '6';
	dest[9] = '4';
	dest[10] = '8';
	dest[11] = '\0';
}

static	char	*valuelimit(int n)
{
	char	*dest;

	if (n == -2147483648)
	{
		dest = malloc (12);
		if (dest == NULL)
			return (NULL);
		attrib_intmin(dest);
	}
	else
	{
		dest = malloc (2);
		if (dest == NULL)
			return (NULL);
		dest[0] = '0';
		dest[1] = '\0';
	}
	return (dest);
}

static char	*ft_reverse_tab(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = 0;
	if (s[j] == '-')
		j++;
	while (s[i])
		i++;
	s[i] = '\0';
	i--;
	while (i > j)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		i--;
		j++;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		i;

	if (n == INT_MIN || n == 0)
		return (valuelimit(n));
	i = 0;
	dest = malloc((ft_count_len(n)));
	if (dest == NULL)
		return (NULL);
	dest[ft_count_len(n) - 1] = '\0';
	if (n < 0)
	{
		n = -n;
		dest[0] = '-';
		i++;
	}
	while (n != 0)
	{
		dest[i] = n % 10 + 48;
		n = n / 10;
		i++;
	}
	dest = ft_reverse_tab(dest);
	return (dest);
}

// int	main(void)
// {
// 	char	*s;
// 	int		n = INT_MIN;

// 	s = ft_itoa(n);
// 	printf("%s\n", s);
// 	// if (n == -2147483648 || n == 0)
// 	// 	return (0);
// 	free (s);
// 	return(0);
// }