/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 06:32:25 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/06 21:17:21 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_test(t_env *e)
{
	t_list	*r;
	t_list	*t;
	t_room	*room;
	t_tube	*tube;

	r = e->r;
	t = e->t;
	printf("==ROOMS==\n");
	while (r)
	{
		room = (t_room*)(r->content);
		printf("{ ID: %d | Name: %s | Type: %d | Ant: %d | Pos y,x: [%d,%d] | Dist: %d }\n", room->id, room->name, room->type, room->ant, room->p.y, room->p.x, room->dist);
		r = r->next;
	}
	printf("==TUBES==\n");
	while (t)
	{
		tube = (t_tube*)(t->content);
		printf("{ R1: %d | R2: %d }\n", tube->r1, tube->r2);
		t = t->next;
	}
}

int		main(void)
{
	t_env	e;

	e.r = NULL;
	e.t = NULL;
	parse_file(&e);
	check_start_end(e.r);
	print_test(&e);
	path_finder(&e, e.r);
	print_test(&e);
	ft_putendl("Launch lem-in");
	return (0);
}
