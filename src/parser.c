/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 13:45:36 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/04 20:14:57 by qhonore          ###   ########.fr       */
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

static int	parse_room(t_env *e, char *line)
{
	char	*tmp;
	char	*name;
	t_pos	pos;

	if (ft_strchr(line, '-'))
		return (0);
	if ((tmp = ft_strchr(line, ' ')) && *(tmp + 1))
	{
		if ((name = ft_strsub(line, 0, tmp - line))
		&& ft_isdigitcstr(++tmp, ' '))
		{//ROOM NAME ALREADY TAKEN
			pos.x = ft_atoi(tmp);
			if ((tmp = ft_strchr(tmp, ' ')) && *(++tmp) && ft_isdigitstr(tmp))
			{
				pos.y = ft_atoi(tmp);
ft_putstr("ROOM: ");
ft_putstr(name);
ft_putchar(' ');
ft_putnbr(pos.x);
ft_putchar(' ');
ft_putnbr(pos.y);
ft_putchar('\n');
(void)e;
				return (1);
			}
		}
	}
	free(line);
	ft_error("Room's wrong format");
	return (-1);
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
				room = parse_room(e, line);
			ft_putendl(line);
		}
		free(line);
	}
	if (line)
		free(line);
}
