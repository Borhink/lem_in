/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:40:42 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/04 19:46:01 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"
// # include "mlx.h"

// # define NOTIFY_MASK (1L<<17)
// # define DESTROYNOTIFY 17

typedef struct s_pos	t_pos;
// typedef struct s_img	t_img;
typedef struct s_room	t_room;
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
	char	*name;
	int		type;
	int		ant;
	t_pos	p;
};

struct	s_tube
{
	char	*r1;
	char	*r2;
};

struct	s_env
{
	// void	*mlx;
	// void	*win;
	// t_img	img;
	int		ants;
	t_list	*rooms;
	t_list	*tubes;
};

void	parse_file(t_env *e);

void	ft_error(char *s);
t_pos	set_pos(int x, int y);

#endif
