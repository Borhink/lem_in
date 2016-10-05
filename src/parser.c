/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 13:45:36 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/05 23:43:49 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_ants_nb(t_env *e)
{
	char	*line;

	if (get_next_line(0, &line) > 0)
	{
		ft_putendl(line);
		e->ants = (ft_isdigitstr(line) ? ft_atoi(line) : 0);
		free(line);
		if (e->ants < 1)
			ft_error("Invalid ants number");
	}
}

static int	get_room_type(char *line)
{
	ft_putendl(line);
	if (!ft_strcmp(line + 2, "start"))
		return (1);
	else if (!ft_strcmp(line + 2, "end"))
		return (2);
	return (0);
}

static int	parse_room(t_env *e, char *line, int type)
{
	char	*tmp;
	t_room	r;

	if (ft_strchr(line, '-'))
		return (0);
	if ((tmp = ft_strchr(line, ' ')) && *(tmp + 1) && tmp - line)
	{
		if (!room_exist(e->r, line, tmp - line) && ft_isdigitcstr(++tmp, ' ')
		&& *tmp != ' ' && (r.name = ft_strsub(line, 0, tmp - line - 1)))
		{
			r.p.x = ft_atoi(tmp);
			if ((tmp = ft_strchr(tmp, ' ')) && *(++tmp) && ft_isdigitstr(tmp))
			{
				r.p.y = ft_atoi(tmp);
				r.ant = 0;
				r.type = type;
				if (!(ft_lstaddend(&(e->r), ft_lstnew(&r, sizeof(t_room)))))
					ft_error("Room's malloc failure");
				return (1);
			}
		}
	}
	free(line);
	ft_error("Room's wrong format");
	return (-1);
}

static int	parse_tube(t_env *e, char *line)
{
	char	*tmp;
	t_tube	t;

	if ((tmp = ft_strchr(line, '-')) && *(tmp + 1) && tmp - line
	&& room_exist(e->r, line, tmp - line) && room_exist(e->r, tmp + 1, -1))
	{
		if ((t.r1 = ft_strsub(line, 0, tmp - line)))
		{
			if ((t.r2 = ft_strdup(++tmp)))
			{
				if (!(ft_lstaddend(&(e->t), ft_lstnew(&t, sizeof(t_tube)))))
					ft_error("Tube's malloc failure");
				return (1);
			}
		}
	}
	return (0);
}

void		parse_file(t_env *e)
{
	char	*line;
	int		type;
	int		room;

	get_ants_nb(e);
	room = 1;
	while (get_next_line(0, &line) > 0 && *line)
	{
		type = 0;
		if (ft_strprefix(line, "##"))
			type = get_room_type(line);
		else if (*line == '#')
			ft_putendl(line);
		else
		{
			if (room)
				room = parse_room(e, line, type);
			if (!room && !parse_tube(e, line))
				break ;
			ft_putendl(line);
		}
		free(line);
	}
	if (line)
		free(line);
}
