/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 11:10:34 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/06 20:40:12 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_error(char *s)
{
	ft_putstr("ERROR: ");
	ft_putendl(s);
	exit(-1);
	return (-1);
}

t_pos	set_pos(int x, int y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

int		room_id(t_list *rooms, char *name, int len)
{
	t_room	*tmp;

	while (rooms)
	{
		tmp = (t_room*)(rooms->content);
		if ((len < 0 && !ft_strcmp(name, tmp->name))
		|| (len >= 0 && !ft_strncmp(name, tmp->name, len)))
			return (tmp->id);
		rooms = rooms->next;
	}
	return (0);
}

t_room	*get_room(t_list *rooms, int id)
{
	t_room	*tmp;

	while (rooms)
	{
		tmp = (t_room*)(rooms->content);
		if (tmp->id == id)
			return (tmp);
		rooms = rooms->next;
	}
	return (NULL);
}

void	check_start_end(t_list *rooms)
{
	t_room	*tmp;
	int		s;
	int		e;

	s = 0;
	e = 0;
	while (rooms)
	{
		tmp = (t_room*)(rooms->content);
		if (tmp->type == 1)
			s = 1;
		else if (tmp->type == 2)
			e = 1;
		if (e && s)
			return ;
		rooms = rooms->next;
	}
	ft_error("Missing start or end");
}
