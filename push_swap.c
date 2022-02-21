/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:07:40 by dcelsa            #+#    #+#             */
/*   Updated: 2022/02/08 20:28:45 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	getval(t_list *lst)
{
	return (*(int *)lst->content);
}

t_bool	sorted(t_list *begin, t_bool lengthmod, t_bool descending)
{
	int	i;

	i = -1;
	while (begin && begin->next && (++i || !i))
	{
		if (!descending && getval(begin) > getval(begin->next))
			return (i * lengthmod);
		if (descending && getval(begin) < getval(begin->next))
			return (i * lengthmod);
		begin = begin->next;
	}
	return ((!lengthmod) + i * lengthmod);
}

static void	sorttriade(t_list **a, t_list **ops, char *stack)
{
	if (!(*a) || ft_lstsize(*a) > 3)
		return ;
	if (ft_lstsize(*a) == 2 && !sorted(*a, FALSE, FALSE))
		swap(a, ops, stack);
	if (ft_lstsize(*a) == 2)
		return ;
	if (!sorted(*a, TRUE, FALSE) && !sorted((*a)->next, FALSE, FALSE))
	{
		swap(a, ops, stack);
		rotate(a, TRUE, ops, stack);
	}
	else if (!sorted(*a, TRUE, FALSE) && getval(*a) > getval(ft_lstlast(*a)))
		rotate(a, FALSE, ops, stack);
	else if (sorted(*a, TRUE, FALSE) && getval(*a) > getval(ft_lstlast(*a)))
		rotate(a, TRUE, ops, stack);
	else if (!sorted(*a, TRUE, FALSE) && getval(*a) < getval(ft_lstlast(*a)))
		swap(a, ops, stack);
	else if (sorted(*a, TRUE, FALSE) && !sorted(*a, FALSE, FALSE))
	{
		swap(a, ops, stack);
		rotate(a, FALSE, ops, stack);
	}
}

static void	sorting(t_list **a, t_list **b, t_list **ops)
{
	t_bool	rev;

	while (ft_lstsize(*a) > 3 && !sorted(*a, FALSE, FALSE))
	{
		if (ft_lstsize(*b) > 1)
			rotating(a, b, ops, FALSE);
		push(a, b, ops, "b\n");
	}
	sorttriade(a, ops, "a\n");
	while (*a && *b)
	{
		rotating(a, b, ops, TRUE);
		push(b, a, ops, "a\n");
	}
	rev = FALSE;
	if (sorted(*a, TRUE, FALSE) + 1 > ft_lstsize(*a) / 2)
		rev = TRUE;
	while (!sorted(*a, FALSE, FALSE))
		rotate(a, rev, ops, "a\n");
	ft_lstclear(a, &free);
	ft_lstclear(b, &free);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	t_list	*ops;
	int		i;

	if (argv++ && argc == 1)
		return (0);
	if (argc == 2)
		argv = ft_split(argv[0], ' ');
	ops = NULL;
	b = NULL;
	a = stackfiller(argv);
	sorting(&a, &b, &ops);
	printops(ops, 0);
	if (argc != 2)
		return (0);
	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
	return (0);
}
