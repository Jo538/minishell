/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_orchestrator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 09:43:08 by admin             #+#    #+#             */
/*   Updated: 2026/04/24 12:23:19 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	helper_free_token_list(t_token *token)
{
	int i = 0;
	t_segment *segment;

	while (i < 3)
	{
		if (i == 0)
		{
			segment = ft_calloc(1, sizeof(t_segment));
			token->segment = segment;
		}
		else 
		{
			segment->next = ft_calloc(1, sizeof(t_segment));
			segment = segment->next;
		}
		segment->value = ft_calloc(1, 3);
		i++;	
	}
}

void	test_free_token_list(void)
{
	int	i = 0;
	t_token	*head;
	t_token	*token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return ;
	while (i < 3)
	{
		if (i > 0)
		{
			token->next = ft_calloc(1, sizeof(t_token));
			token = token->next;			
		}
		if (i == 0)
			head = token;
		helper_free_token_list(token);
		i++;	
	}
	free_token_list(head);
}

void	helper_test_lexer_orchestrator(t_token *expected, t_token *actual)
{
	
}
void	test_lexer_orchestrator(void)
{
	t_token *actual;
	t_token *expected[] = {
		{NULL, ON_WORD, &(t_segment){"echo", UNQUOTED, NULL}, &(t_token){NULL, ON_WORD, &(t_segment){"hello", UNQUOTED, &(t_segment){"world", D_QUOTED, NULL}}}}
	};
	
	helper_test_lexer_orchestrator()
}