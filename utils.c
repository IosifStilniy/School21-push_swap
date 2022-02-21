/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:08:20 by dcelsa            #+#    #+#             */
/*   Updated: 2022/02/08 20:25:41 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_handler(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

t_ui	diffunc(int a, int b)
{
	if (a > b)
		return (a - b);
	else
		return (b - a);
}

static int	numchecker(int num, t_list *begin, char *str)
{
	int	count;
	int	cpy;
	int	i;

	i = -1;
	while (str[++i])
		if (!('0' <= str[i] && str[i] <= '9') && str[i] != '-' && str[i] != '+')
			error_handler();
	cpy = num;
	count = 1 + (cpy < 0);
	while (cpy / 10)
	{
		count++;
		cpy /= 10;
	}
	while (begin)
	{
		if (getval(begin) == num)
			error_handler();
		begin = begin->next;
	}
	return (count);
}

t_list	*stackfiller(char **argv)
{
	int		*num;
	int		i;
	int		size;
	t_list	*begin;

	i = 0;
	while (argv[i])
		i++;
	size = i;
	begin = NULL;
	while (i--)
	{
		num = malloc(sizeof(*num));
		*num = ft_atoi(argv[i]);
		if (numchecker(*num, begin, argv[i]) != (int)ft_strlen(argv[i]))
			error_handler();
		ft_lstadd_front(&begin, ft_lstnew((void *)num));
	}
	if (ft_lstsize(begin) != size)
		error_handler();
	return (begin);
}

void	printops(t_list *ops, int i)
{
	if (!ops)
		return ;
	if (ops->next)
		printops(ops->next, i + 1);
	ft_putstr_fd((char *)ops->content, 1);
	if (!i)
		ft_lstclear(&ops, &free);
}
