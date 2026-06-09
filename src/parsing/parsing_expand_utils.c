/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:05:02 by bribot            #+#    #+#             */
/*   Updated: 2026/06/09 14:07:14 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors_siv(char *str, int allocated, char *to_return)
{
	free(str);
	if (allocated)
		free(to_return);
}