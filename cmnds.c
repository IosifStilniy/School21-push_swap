/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:07:38 by dcelsa            #+#    #+#             */
/*   Updated: 2022/02/07 23:21:08 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	minmaxdefiner(t_list *dst, t_minmaxdif *minmax)
{
	int		c;

	minmax->min = getval(dst);
	minmax->max = getval(dst);
	minmax->dif = UINT32_MAX;
	minmax->pos = INT32_MAX;
	minmax->prev = getval(ft_lstlast(dst));
	minmax->over = FALSE;
	c = 0;
	while (dst && ++c)
	{
		if (getval(dst) < minmax->min)
			minmax->min = getval(dst);
		if (getval(dst) > minmax->max)
			minmax->max = getval(dst);
		dst = dst->next;
	}
}

static t_bool	trace(t_list *src, t_list *dst, t_minmaxdif *nx, t_bool dsc)
{
	t_ui	dif;

	if (getval(src) < nx->min || getval(src) > nx->max)
	{
		if ((dsc && getval(dst) == nx->max)
			|| (!dsc && getval(dst) == nx->min))
		{
			nx->over = TRUE;
			return (1);
		}
		return (0);
	}
	if (!((dsc && nx->prev > getval(src) && getval(src) > getval(dst))
			|| (!dsc && nx->prev < getval(src) && getval(src) < getval(dst))))
		return (0);
	dif = diffunc(nx->prev, getval(dst));
	if (dif > nx->dif)
		return (0);
	nx->dif = dif;
	return (1);
}

static int	fasttrace(t_list *st, t_list *rot, t_bool dsc)
{
	int			c;
	t_minmaxdif	minmax;

	minmaxdefiner(rot, &minmax);
	c = 0;
	while (rot && ++c)
	{
		if (trace(st, rot, &minmax, dsc))
			minmax.pos = c;
		minmax.prev = getval(rot);
		if (minmax.over)
			break ;
		rot = rot->next;
	}
	return (minmax.pos);
}

void	tracedefiner(t_list *a, t_list *b, int pos[2], t_rotpar *rotpar)
{
	t_ui	tr[4];
	t_ui	min;
	int		i[2];

	tr[0] = pos[0] + diffunc(pos[0], pos[1]);
	tr[1] = ft_lstsize(a) - pos[0] + 1
		+ diffunc(ft_lstsize(a) - pos[0], ft_lstsize(b) - pos[1]);
	tr[2] = ft_lstsize(a) - pos[0] + 1 + pos[1];
	tr[3] = pos[0] + ft_lstsize(b) - pos[1] + 1;
	min = tr[0];
	i[0] = -1;
	while (++i[0] < 4)
	{
		if (tr[i[0]] > min || tr[i[0]] < 0)
			continue ;
		min = tr[i[0]];
		i[1] = i[0];
	}
	if (min >= rotpar->min || min < 0)
		return ;
	rotpar->min = min;
	rotpar->rev[0] = (i[1] == 1 || i[1] == 2);
	rotpar->rev[1] = (i[1] == 1 || i[1] == 3);
	rotpar->pos[0] = pos[0] - 1;
	rotpar->pos[1] = pos[1] - 1;
}

void	rotating(t_list **a, t_list **b, t_list **ops, t_bool pusha)
{
	int			pos[2];
	t_rotpar	rotpar;
	t_list		*cpy;

	cpy = *a;
	if (pusha)
		cpy = *b;
	rotpar.min = INT32_MAX;
	pos[pusha] = 0;
	while (cpy && ++pos[pusha])
	{
		if (!pusha)
			pos[!pusha] = fasttrace(cpy, *b, !pusha);
		else
			pos[!pusha] = fasttrace(cpy, *a, !pusha);
		tracedefiner(*a, *b, pos, &rotpar);
		cpy = cpy->next;
	}
	if (rotpar.rev[0] == rotpar.rev[1] && rotpar.pos[1])
		rotpar.stack = ft_strjoin("r\n", NULL);
	else
		rotpar.stack = ft_strjoin("a\n", NULL);
	turnon(a, b, ops, &rotpar);
	free(rotpar.stack);
}
