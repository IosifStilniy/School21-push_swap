/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_cmnds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:07:36 by dcelsa            #+#    #+#             */
/*   Updated: 2022/02/07 23:20:54 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"push_swap.h"

static t_list	*recops(t_list *ops, char *op)
{
	t_list	*new;

	if (!op)
		error_handler();
	new = ft_lstnew((void *)op);
	if (!new)
		error_handler();
	ft_lstadd_front(&ops, new);
	return (ops);
}

void	swap(t_list **head, t_list **ops, char *stack)
{
	t_list	*tmp;

	if (!(*head) || !(*head)->next)
		return ;
	tmp = (*head)->next;
	(*head)->next = tmp->next;
	tmp->next = *head;
	*head = tmp;
	*ops = recops(*ops, ft_strjoin("s", stack));
}

void	push(t_list **from, t_list **to, t_list **ops, char *stack)
{
	t_list	*tmp;

	if (!(*from))
		return ;
	tmp = (*from)->next;
	(*from)->next = *to;
	*to = *from;
	*from = tmp;
	*ops = recops(*ops, ft_strjoin("p", stack));
}

void	rotate(t_list **head, t_bool reverse, t_list **ops, char *stack)
{
	t_list	*prevtail;
	t_list	*tmp;

	if (!(*head) || !(*head)->next)
		return ;
	prevtail = *head;
	while (prevtail->next->next)
		prevtail = prevtail->next;
	prevtail->next->next = *head;
	if (!reverse)
	{
		tmp = (*head)->next;
		(*head)->next = NULL;
		*head = tmp;
		if (stack)
			*ops = recops(*ops, ft_strjoin("r", stack));
	}
	else
	{
		*head = prevtail->next;
		prevtail->next = NULL;
		if (stack)
			*ops = recops(*ops, ft_strjoin("rr", stack));
	}
}

void	turnon(t_list **a, t_list **b, t_list **ops, t_rotpar *rp)
{
	t_bool	rotb;

	rotb = FALSE;
	if (rp->rev[0])
		rp->pos[0] = ft_lstsize(*a) - rp->pos[0];
	if (rp->rev[1])
		rp->pos[1] = ft_lstsize(*b) - rp->pos[1];
	if (rp->rev[0] && rp->rev[0] == rp->rev[1] && rp->pos[1] && ++rotb)
		rp->pos[1] = (rp->pos[0] % ft_lstsize(*b)) - rp->pos[1];
	if (!rp->rev[0] && rp->rev[0] == rp->rev[1] && rp->pos[1] && ++rotb)
		rp->pos[1] = rp->pos[1] - (rp->pos[0] % ft_lstsize(*b));
	while (rp->pos[0]--)
	{
		if (rp->rev[0] == rp->rev[1] && rotb)
			rotate(b, rp->rev[1], ops, NULL);
		rotate(a, rp->rev[0], ops, rp->stack);
	}
	if (rp->rev[0] == rp->rev[1])
	{
		rp->rev[1] = FALSE;
		if (rp->pos[1] < 0 && ++rp->rev[1])
			rp->pos[1] *= -1;
	}
	while (rp->pos[1]--)
		rotate(b, rp->rev[1], ops, "b\n");
}
