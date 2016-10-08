/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 18:21:27 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/08 17:01:43 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*add_connected(t_env *e, t_room *r, t_list *t)
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
			if ((!(tmp->dist) || tmp->dist > r->dist + 1) && tmp->type != 2)
			{
				tmp->dist = r->dist + 1;
				return (tmp);
			}
		}
		t = t->next;
	}
	return (NULL);
}

static t_room	*get_connected(t_env *e, t_room *r, t_list *t)
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
			if (!(tmp->path) && tmp->dist < r->dist && tmp->type != 1)
			{
				tmp->path = e->paths + 1;
				return (tmp);
			}
			else if (tmp->type == 2)
				e->paths++;
		}
		t = t->next;
	}
	return (NULL);
}

static int		get_path(t_env *e, t_list *r, t_list *t, t_room *cur)
{
	t_room	*room;

	while ((room = add_connected(e, cur, t)))
	{
		if (room->type != 1)
			get_path(e, r, t, room);
	}
	return (0);
}

static void		path_checker(t_env *e, t_list *r, t_list *t, t_room *cur)
{
	t_room	*room;

	while ((room = get_connected(e, cur, t)))
	{
		if (room->type != 2)
			path_checker(e, r, t, room);
	}
}

void			path_finder(t_env *e, t_list *r)
{
	t_room	*room;

	while (r)
	{
		room = (t_room*)(r->content);
		if (room->type == 2)
			get_path(e, e->r, e->t, room);
		r = r->next;
	}
	r = e->r;
	while (r)
	{
		room = (t_room*)(r->content);
		if (room->type == 1 && room->dist)
			path_checker(e, e->r, e->t, room);
		r = r->next;
	}
	if (!e->paths)
		ft_error("0 path found");
}
