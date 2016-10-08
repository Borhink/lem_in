/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:40:42 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/08 19:23:33 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
#include<stdio.h>
// # include "mlx.h"

// # define NOTIFY_MASK (1L<<17)
// # define DESTROYNOTIFY 17

typedef struct s_pos	t_pos;
// typedef struct s_img	t_img;
typedef struct s_room	t_room;
typedef struct s_tube	t_tube;
typedef struct s_env	t_env;

struct	s_pos
{
	int		x;
	int		y;
};

// struct	s_img
// {
// 	void	*i;
// 	char	*d;
// 	int		bpp;
// 	int		sl;
// 	int		edn;
// };

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
	// void	*mlx;
	// void	*win;
	// t_img	img;
	int		in;
	int		ants;
	int		paths;
	int		left;
	t_list	*r;
	t_list	*t;
};

void	parse_file(t_env *e);

int		ft_error(char *s);
t_pos	set_pos(int x, int y);
int		room_id(t_list *rooms, char *name, int len);
void	check_start_end(t_list *rooms);
t_room	*get_room(t_list *rooms, int id);

void	path_finder(t_env *e, t_list *r);
void	get_out(t_env *e, t_list *r);
void	move_path(t_env *e, t_room *cur, int path);

#endif
