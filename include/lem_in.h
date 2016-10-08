/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:40:42 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/09 00:02:05 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct s_pos	t_pos;
typedef struct s_room	t_room;
typedef struct s_tube	t_tube;
typedef struct s_env	t_env;

struct	s_pos
{
	int		x;
	int		y;
};

struct	s_room
{
	int		id;
	int		path;
	char	*name;
	int		type;
	int		ant;
	int		dist;
	t_pos	p;
};

struct	s_tube
{
	int		r1;
	int		r2;
};

struct	s_env
{
	t_list	*r;
	t_list	*t;
	t_list	*f;
	int		in;
	int		ants;
	int		paths;
	int		left;
	int		first;
};

int		ft_error(t_env *e, char *s);
void	free_all(t_list *r, t_list *t, t_list *f, t_list *tmp);
t_pos	set_pos(int x, int y);
int		room_id(t_list *rooms, char *name, int len);
void	check_start_end(t_env *e, t_list *rooms);
t_room	*get_room(t_list *rooms, int id);
int		get_room_type(t_env *e, char *line);

void	path_finder(t_env *e, t_list *r);
void	get_out(t_env *e, t_list *r);
void	move_path(t_env *e, t_room *cur, int path);
void	parse_file(t_env *e, int type);

#endif
