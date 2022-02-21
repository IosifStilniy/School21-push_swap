/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:07:40 by dcelsa            #+#    #+#             */
/*   Updated: 2022/02/09 18:24:42 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static void	cleaner(char **argv, t_list *a, t_list *b, int argc)
{
	int	i;

	ft_lstclear(&a, &free);
	ft_lstclear(&b, &free);
	if (argc != 2)
		return ;
	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

static void	readndo(int pfd[2], t_list **a, t_list **b)
{
	char	*buf;

	pipe(pfd);
	buf = get_next_line(0);
	while (buf)
	{
		write(pfd[1], buf, ft_strlen(buf));
		if (buf)
			free(buf);
		buf = get_next_line(0);
	}
	if (buf)
		free(buf);
	close(pfd[1]);
	buf = get_next_line(pfd[0]);
	while (buf)
	{
		executor(a, b, buf);
		if (buf)
			free(buf);
		buf = get_next_line(pfd[0]);
	}
	close(pfd[0]);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	int		pfd[2];

	if (argc == 1)
		return (0);
	if (argv++ && argc == 2)
		argv = ft_split(argv[0], ' ');
	b = NULL;
	a = stackfiller(argv);
	readndo(pfd, &a, &b);
	if (sorted(a) && !b)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	cleaner(argv, a, b, argc);
	return (0);
}
