/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 18:21:27 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/06 22:09:50 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// static void		add_dist(t_env *e, t_room *r, t_list *t)
// {
// 	t_room	*tmp;
// 	t_tube	*tube;
//
// 	while (t)
// 	{
// 		tube = (t_tube*)(t->content);
// 		if (tube->r1 == r->id && tube->r1 != tube->r2)
// 		{
// 			tmp = get_room(e->r, tube->r2);
// 			if (!(tmp->dist) && tmp->type != 1)
// 				tmp->dist = r->dist + 1;
// 		}
// 		else if (tube->r2 == r->id && tube->r1 != tube->r2)
// 		{
// 			tmp = get_room(e->r, tube->r1);
// 			if (!(tmp->dist) && tmp->type != 1)
// 				tmp->dist = r->dist + 1;
// 		}
// 		t = t->next;
// 	}
// }

static t_room	*get_connected(t_env *e, t_room *r, t_list *t)
{
	t_room	*tmp;
	t_tube	*tube;

	while (t)
	{
		tube = (t_tube*)(t->content);
		if (tube->r1 == r->id && tube->r1 != tube->r2)
		{
			tmp = get_room(e->r, tube->r2);
			if (!(tmp->dist) && tmp->type != 1)
			{
				tmp->dist = r->dist + 1;
				printf("Add dist to %d -> %d\n", tmp->id, tmp->dist);
				return (tmp);
			}
		}
		else if (tube->r2 == r->id && tube->r1 != tube->r2)
		{
			tmp = get_room(e->r, tube->r1);
			if (!(tmp->dist) && tmp->type != 1)
			{
				tmp->dist = r->dist + 1;
				printf("Add dist to %d -> %d\n", tmp->id, tmp->dist);
				return (tmp);
			}
		}
		t = t->next;
	}
	return (NULL);
}

static int	get_path(t_env *e, t_list *r, t_list *t, t_room *cur)
{
	t_room	*room;
	int		end;

	printf("START ROOM %d\n", cur->id);
	// add_dist(e, cur, t);
	while ((room = get_connected(e, cur, t)))
	{
		if (room->type == 2)
		{
			printf("WAY FOUND ROOM %d\n", room->id);
			return (room->id);
		}
		if ((end = get_path(e, r, t, room)))
		{
			printf("WAY FOUND ROOM %d\n", room->id);
			return (end);
		}
	}
	printf("NO WAY ROOM %d\n", cur->id);
	return (0);
}

void			path_finder(t_env *e, t_list *r)
{
	t_room	*room;
	int		end;

	while (r)
	{
		room = (t_room*)(r->content);
		if (room->type == 1)
		{
			printf("BEGIN FINDING, START = %d\n", room->id);
			end = get_path(e, e->r, e->t, room);
			printf("END = %d\n", end);
			printf("END FINDING, START = %d\n", room->id);
		}
		r = r->next;
	}
}
