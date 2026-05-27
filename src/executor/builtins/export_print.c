/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by admin             #+#    #+#             */
/*   Updated: 2026/05/27 12:00:00 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env_ptrs(t_env **sorted, int count)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strncmp(sorted[j]->key, sorted[j + 1]->key,
					max(sorted[j]->key, sorted[j + 1]->key)) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_sorted(t_env **sorted, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (sorted[i]->export_flag)
		{
			printf("export %s", sorted[i]->key);
			if (sorted[i]->set_flag)
				printf("=\"%s\"", sorted[i]->value);
			printf("\n");
		}
		i++;
	}
}

void	print_var(t_env **my_env)
{
	int		i;
	int		count;
	t_env	**sorted;

	count = 0;
	while (my_env[count])
		count++;
	sorted = ft_calloc(count + 1, sizeof(t_env *));
	if (!sorted)
		return ;
	i = 0;
	while (i < count)
	{
		sorted[i] = my_env[i];
		i++;
	}
	sort_env_ptrs(sorted, count);
	print_sorted(sorted, count);
	free(sorted);
}
