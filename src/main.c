/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 06:32:25 by qhonore           #+#    #+#             */
/*   Updated: 2016/10/08 19:23:06 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_env	e;

	e.r = NULL;
	e.t = NULL;
	e.paths = 0;
	parse_file(&e);
	check_start_end(e.r);
	path_finder(&e, e.r);
	ft_putchar('\n');
	get_out(&e, e.r);
	return (0);
}
