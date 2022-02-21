/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_cmnds_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:07:36 by dcelsa            #+#    #+#             */
/*   Updated: 2022/02/09 18:25:31 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static void	swap(t_list **head, t_list **a, t_list **b)
{
	t_list	*tmp;

	if (!head)
	{
		swap(b, a, b);
		head = a;
	}
	if (!(*head) || !(*head)->next)
		return ;
	tmp = (*head)->next;
	(*head)->next = tmp->next;
	tmp->next = *head;
	*head = tmp;
}

static void	push(t_list **act, t_list **a, t_list **b)
{
	t_list	*tmp;
	t_list	**from;

	from = a;
	if (act == a)
		from = b;
	if (!(*from))
		return ;
	tmp = (*from)->next;
	(*from)->next = *act;
	*act = *from;
	*from = tmp;
}

static int	rotate(t_list **head, t_list **a, t_list **b, t_bool reverse)
{
	t_list	*prevtail;
	t_list	*tmp;

	if (!head && *b && rotate(b, a, b, reverse))
		head = a;
	if (!head)
		return (1);
	if (!(*head) || !(*head)->next)
		return (1);
	prevtail = *head;
	while (prevtail->next->next)
		prevtail = prevtail->next;
	prevtail->next->next = *head;
	if (!reverse)
	{
		tmp = (*head)->next;
		(*head)->next = NULL;
		*head = tmp;
		return (1);
	}
	*head = prevtail->next;
	prevtail->next = NULL;
	return (1);
}

void	executor(t_list **a, t_list **b, char *cmd)
{
	t_list	**act;

	act = NULL;
	if (cmd[ft_strlen(cmd) - 2] == 'a')
		act = a;
	else if (cmd[ft_strlen(cmd) - 2] == 'b')
		act = b;
	if (ft_strlen(cmd) > 4 || ft_strlen(cmd) < 3
		|| (cmd[1] != 'a' && cmd[1] != 'b' && cmd[1] != cmd[0]))
		error_handler();
	if (cmd[0] == 's')
		swap(act, a, b);
	else if (cmd[0] == 'p')
		push(act, a, b);
	else if (cmd[0] == 'r')
	{
		if (ft_strlen(cmd) == 4)
			rotate(act, a, b, TRUE);
		else
			rotate(act, a, b, FALSE);
	}
	else
		error_handler();
}
