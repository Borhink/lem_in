/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 11:10:34 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/09 00:03:10 by qhonore          ###   ########.fr       */
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
	return (0);
}
