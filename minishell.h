/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 15:13:06 by benji             #+#    #+#             */
/*   Updated: 2026/04/07 13:28:04 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "LIBS/printf/ft_printf.h"

//PAS CERTAIN QUE CE SOIT LES BONNES LIBS
# include <readline/readline.h>
# include <readline/history.h>

char*	prompt(void);



# endif
