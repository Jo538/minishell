/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:07:59 by bribot            #+#    #+#             */
/*   Updated: 2025/11/19 14:39:13 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isalpha(int s)
{
	if ((s > 64 && s < 91) || (s > 96 && s < 123))
		return (1);
	else
		return (0);
}

static	int	ft_isdigit(int n)
{
	if (n > 47 && n < 58)
		return (1);
	return (0);
}

int	ft_isalnum(int n)
{
	if (ft_isalpha(n) || ft_isdigit(n))
		return (1);
	else
		return (0);
}
