/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 06:32:25 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/09 00:03:17 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_anthill(t_list *f)
{
	while (f)
	{
		ft_putendl((char*)(f->content));
		f = f->next;
	}
}

int			main(void)
{
	t_env	e;

	e.r = NULL;
	e.t = NULL;
	e.f = NULL;
	e.paths = 0;
	parse_file(&e, 0);
	check_start_end(&e, e.r);
	path_finder(&e, e.r);
	print_anthill(e.f);
	ft_putchar('\n');
	get_out(&e, e.r);
	free_all(e.r, e.t, e.f, NULL);
	return (0);
}
