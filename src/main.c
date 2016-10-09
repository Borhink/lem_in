/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 06:32:25 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/09 15:59:48 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	follow_path(t_env *e, t_room *cur, int path, int *first)
{
	t_room	*room;

	while ((room = get_path_way(e, cur, e->t, path)))
	{
		follow_path(e, room, path, first);
		if (*first)
		{
			ft_putstr(" : ");
			*first = 0;
		}
		else
			ft_putstr(" -> ");
		ft_putstr(room->name);
		return (1);
	}
	return (0);
}

static void	print_paths(t_env *e, t_list *r, int path)
{
	t_room	*room;
	int		first;

	if (e->vpath)
	{
		while (++path <= e->paths)
		{
			first = 1;
			ft_putstr("Path ");
			ft_putnbr(path);
			while (r)
			{
				room = (t_room*)(r->content);
				if (room->type == 2 && follow_path(e, room, path, &first))
				{
					ft_putstr(" -> ");
					ft_putstr(room->name);
				}
				r = r->next;
			}
			ft_putchar('\n');
			r = e->r;
		}
		ft_putchar('\n');
	}
}

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
	e.vpath = 0;
	e.step = 0;
	e.info = 0;
	parse_file(&e, 0);
	check_start_end(&e, e.r);
	path_finder(&e, e.r);
	print_anthill(e.f);
	ft_putchar('\n');
	print_paths(&e, e.r, 0);
	get_out(&e, e.r);
	if (e.info)
		ft_putstr("After a long adventure, we finaly leaved the anthill !\n");
	return (0);
}
