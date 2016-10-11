/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 13:45:36 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/11 14:38:49 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	get_ants_nb(t_env *e)
{
	char	*line;

	if (get_next_line(0, &line) > 0)
	{
		if (!(ft_lstaddend(&(e->f), ft_lstnew(line, ft_strlen(line) + 1))))
			ft_error(e, "File's malloc failure");
		e->ants = (ft_isdigitstr(line) ? ft_atoi(line) : 0);
		free(line);
		if (e->ants < 1)
			ft_error(e, "Invalid ants number");
	}
	return (1);
}

static void	init_room(t_room *r, int type, int id)
{
	r->ant = 0;
	r->type = type;
	r->id = id;
	r->dist = 0;
	r->path = 0;
}

static int	parse_room(t_env *e, char *line, int type, int id)
{
	char	*tmp;
	t_room	r;

	if (ft_strchr(line, '-'))
		return (0);
	if (*line != 'L' && (tmp = ft_strchr(line, ' '))
	&& *(tmp + 1) && tmp - line)
	{
		if (!room_id(e->r, line, tmp - line) && ft_isdigitcstr(++tmp, ' ')
		&& *tmp != ' ' && (r.name = ft_strsub(line, 0, tmp - line - 1)))
		{
			r.p.x = ft_atoi(tmp);
			if ((tmp = ft_strchr(tmp, ' ')) && *(++tmp) && ft_isdigitstr(tmp))
			{
				r.p.y = ft_atoi(tmp);
				init_room(&r, type, id);
				if (!(ft_lstaddend(&(e->r), ft_lstnew(&r, sizeof(t_room)))))
					ft_error(e, "Room's malloc failure");
				return (id + 1);
			}
		}
	}
	free(line);
	return (ft_error(e, "Room's wrong format"));
}

static int	parse_tube(t_env *e, char *line)
{
	char	*tmp;
	t_tube	t;

	if ((tmp = ft_strchr(line, '-')) && *(tmp + 1) && tmp - line
	&& room_id(e->r, line, tmp - line) && room_id(e->r, tmp + 1, -1))
	{
		t.r1 = room_id(e->r, line, tmp - line);
		t.r2 = room_id(e->r, ++tmp, -1);
		if (!(ft_lstaddend(&(e->t), ft_lstnew(&t, sizeof(t_tube)))))
			ft_error(e, "Tube's malloc failure");
		return (1);
	}
	return (0);
}

void		parse_file(t_env *e, int type)
{
	char	*line;
	int		room;

	room = get_ants_nb(e);
	while (get_next_line(0, &line) > 0 && *line)
	{
		if (ft_strprefix(line, "##"))
			type = get_room_type(e, line);
		else if (*line == '#')
			ft_lstaddend(&(e->f), ft_lstnew(line, ft_strlen(line) + 1));
		else
		{
			if (room)
				room = parse_room(e, line, type, room);
			if (!room && !parse_tube(e, line))
				break ;
			if (!(ft_lstaddend(&(e->f), ft_lstnew(line, ft_strlen(line) + 1))))
				ft_error(e, "File's malloc failure");
			type = 0;
		}
		free(line);
	}
	if (line)
		free(line);
}
