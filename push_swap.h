/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:07:45 by dcelsa            #+#    #+#             */
/*   Updated: 2022/02/08 20:28:31 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

typedef int				t_bool;
typedef unsigned int	t_ui;

typedef struct s_minmaxdif {
	int		min;
	int		max;
	t_ui	dif;
	int		pos;
	int		prev;
	t_bool	over;
}	t_minmaxdif;

typedef struct s_rotpar {
	int		pos[2];
	t_bool	rev[2];
	t_ui	min;
	char	*stack;
}	t_rotpar;

int		getval(t_list *lst);
void	error_handler(void);
void	swap(t_list **head, t_list **ops, char *stack);
void	push(t_list **from, t_list **to, t_list **ops, char *stack);
void	rotate(t_list **head, t_bool reverse, t_list **ops, char *stack);
void	printops(t_list *ops, int i);
void	rotating(t_list **a, t_list **b, t_list **ops, t_bool pusha);
void	turnon(t_list **a, t_list **b, t_list **ops, t_rotpar *rotpar);
t_ui	diffunc(int a, int b);
t_bool	sorted(t_list *begin, t_bool lengthmod, t_bool descending);
t_list	*stackfiller(char **argv);

#endif
