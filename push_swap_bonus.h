/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:07:45 by dcelsa            #+#    #+#             */
/*   Updated: 2022/02/08 20:35:04 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H
# include "libft.h"
# include "GetNextLine/get_next_line.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef int				t_bool;
typedef unsigned int	t_ui;

void	error_handler(void);
void	executor(t_list **a, t_list **b, char *cmd);
t_bool	sorted(t_list *begin);
t_list	*stackfiller(char **argv);

#endif