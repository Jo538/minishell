/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:17:18 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/18 14:55:43 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The toupper() function returns the ASCII value of an uppercase 
 * version of the character. If the character is not an uppercase character 
 * then its value is returned without being changed.
 * 
 * @param c The ASCII value of a character or an actual character .
 * @return int An int value representing the ASCII value of the uppercase 
 * version of a character.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}
/*
int	main(void)
{
	int	c;

	c = 259;
	printf("%c\n", toupper(c));
	c = 259;
	printf("%c\n", ft_toupper(c));
}*/