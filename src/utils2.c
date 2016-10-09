/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 11:10:34 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/09 15:55:06 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_all(t_list *r, t_list *t, t_list *f, t_list *tmp)
{
	t_room	*room;

	while (r)
	{
		room = (t_room*)(r->content);
		free(room->name);
		free(room);
		tmp = r;
		r = r->next;
		free(tmp);
	}
	while (t)
	{
		free(t->content);
		tmp = t;
		t = t->next;
		free(tmp);
	}
	while (f)
	{
		free(f->content);
		tmp = f;
		f = f->next;
		free(tmp);
	}
}

int		ft_error(t_env *e, char *s)
{
	ft_putstr("ERROR: ");
	ft_putendl(s);
	free_all(e->r, e->t, e->f, NULL);
	exit(-1);
	return (-1);
}

int		get_room_type(t_env *e, char *line)
{
	if (!(ft_lstaddend(&(e->f), ft_lstnew(line, sizeof(char*)))))
		ft_error(e, "File's malloc failure");
	if (!ft_strcmp(line + 2, "start"))
		return (1);
	else if (!ft_strcmp(line + 2, "end"))
		return (2);
	else if (!ft_strcmp(line + 2, "paths"))
		e->vpath = 1;
	else if (!ft_strcmp(line + 2, "step"))
		e->step = 1;
	else if (!ft_strcmp(line + 2, "info"))
		e->info = 1;
	return (0);
}

void	print_info(t_env *e, t_room *cur, t_room *next)
{
	if (e->first)
	{
		ft_putstr("\033[32m==== TURN ");
		ft_putnbr(e->turn);
		ft_putstr(" ====\033[0m\n");
		e->first = 0;
	}
	ft_putstr("\033[33mAnt ");
	ft_putnbr(next->ant);
	ft_putstr(":\n\033[0mLeave room \033[33m");
	ft_putstr(cur->name);
	ft_putstr("\033[0m to \033[33m");
	ft_putstr(next->name);
	ft_putstr("\033[0m\nThe nearest end is \033[31m");
	ft_putstr(e->near);
	ft_putstr("\033[0m (\033[33m");
	ft_putnbr(next->dist);
	if (next->dist < 2)
		ft_putstr("\033[0m turn to go)\n\n");
	else
		ft_putstr("\033[0m turns to go)\n\n");
	if (e->step)
		usleep(1500000);
}
