/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:09:53 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/09 15:55:10 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_ant(t_env *e, t_room *cur)
{
	if (e->first)
		e->first = 0;
	else
		ft_putchar(' ');
	ft_putchar('L');
	ft_putnbr(cur->ant);
	ft_putchar('-');
	ft_putstr(cur->name);
	if (e->step)
		usleep(500000);
}

t_room		*get_path_way(t_env *e, t_room *r, t_list *t, int path)
{
	t_room	*tmp;
	t_tube	*tube;

	while (t)
	{
		tube = (t_tube*)(t->content);
		if (tube->r1 != tube->r2 && (tube->r1 == r->id || tube->r2 == r->id))
		{
			if (tube->r1 == r->id)
				tmp = get_room(e->r, tube->r2);
			else
				tmp = get_room(e->r, tube->r1);
			if ((tmp->path == path || tmp->type == 1) && tmp->dist > r->dist)
				return (tmp);
		}
		t = t->next;
	}
	return (NULL);
}

static void	type_one(t_env *e, t_room *room, t_room *cur, int path)
{
	if (e->in < e->ants)
	{
		cur->ant = ++(e->in);
		e->info ? print_info(e, room, cur) : print_ant(e, cur);
		if (cur->type == 2)
		{
			--(e->left);
			move_path(e, cur, path);
		}
	}
}

void		move_path(t_env *e, t_room *cur, int path)
{
	t_room	*room;

	while ((room = get_path_way(e, cur, e->t, path)))
	{
		if ((cur->type == 2 || !cur->ant) && room->type == 1)
			return (type_one(e, room, cur, path));
		else
		{
			if ((cur->type == 2 || !cur->ant) && room->ant > 0)
			{
				if (cur->type == 2)
					--(e->left);
				cur->ant = room->ant;
				room->ant = 0;
				e->info ? print_info(e, room, cur) : print_ant(e, cur);
			}
			move_path(e, room, path);
			return ;
		}
	}
}

void		get_out(t_env *e, t_list *r)
{
	t_room	*room;
	int		path;

	e->in = 0;
	e->left = e->ants;
	e->turn = 1;
	while (e->left)
	{
		while (r)
		{
			room = (t_room*)(r->content);
			e->first = 1;
			if (room->type == 2)
			{
				path = 0;
				e->near = room->name;
				while (++path <= e->paths)
					move_path(e, room, path);
			}
			r = r->next;
		}
		r = e->r;
		ft_putchar('\n');
		++e->turn;
	}
}
