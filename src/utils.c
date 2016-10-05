/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 11:10:34 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/05 18:42:11 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_error(char *s)
{
	ft_putstr("ERROR: ");
	ft_putendl(s);
	exit(-1);
}

t_pos	set_pos(int x, int y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

int		room_exist(t_list *rooms, char *name, int len)
{
	t_room	*tmp;

	while (rooms)
	{
		tmp = (t_room*)(rooms->content);
		if ((len < 0 && !ft_strcmp(name, tmp->name))
		|| (len >= 0 && !ft_strncmp(name, tmp->name, len)))
			return (1);
		rooms = rooms->next;
	}
	return (0);
}
