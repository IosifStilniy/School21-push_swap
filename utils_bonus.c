/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:08:20 by dcelsa            #+#    #+#             */
/*   Updated: 2022/02/08 20:33:01 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static int	getval(t_list *lst)
{
	return (*(int *)lst->content);
}

void	error_handler(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
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

t_bool	sorted(t_list *begin)
{
	while (begin && begin->next)
	{
		if (getval(begin) > getval(begin->next))
			return (FALSE);
		begin = begin->next;
	}
	return (TRUE);
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
