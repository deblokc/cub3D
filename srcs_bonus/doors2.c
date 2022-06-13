/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:07:37 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/13 15:39:25 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_next_door_point(t_proj *proj, int c[2], int vect, \
			double next[2])
{
	int	pendant;

	pendant = vect ^ 1;
	next[vect] = (double)c[vect] + 0.9999;
	next[pendant] = (fabs(next[vect] - proj->cur[vect]) / fabs(proj->v[vect])) \
					* proj->v[pendant] + proj->cur[pendant];
	if (proj->v[vect] < 0)
	{
		next[vect] = (double)c[vect];
		next[pendant] = (fabs(next[vect] - proj->cur[vect]) \
				/ fabs(proj->v[vect])) * proj->v[pendant] + proj->cur[pendant];
	}
}

static int	visible_door(t_proj *proj, double coords[2])
{
	proj->is_door = 1;
	proj->cur[0] = coords[0];
	proj->cur[1] = coords[1];
	return (1);
}

int	is_on_door(t_info *info, t_proj *proj, int hit)
{
	int		c[2];
	int		vect;
	int		pendant;
	double	visible[2];
	double	next[2];

	c[0] = (int)proj->cur[0];
	c[1] = (int)proj->cur[1];
	if (info->map[c[1]][c[0]] != '2')
		return (0);
	proj->door = find_door(info, c);
	if (!proj->door)
		return (0);
	vect = 0;
	if (hit == 1)
		vect = 1;
	pendant = vect ^ 1;
	visible[0] = c[pendant];
	visible[1] = visible[0] + (double)proj->door->visible / 100;
	if (proj->cur[pendant] >= visible[0] && proj->cur[pendant] <= visible[1])
		return (visible_door(proj, proj->cur));
	get_next_door_point(proj, c, vect, next);
	if (next[pendant] >= visible[0] && next[pendant] <= visible[1])
		return (visible_door(proj, next));
	return (0);
}

int	set_door_texture(t_info *info, t_proj *proj, int vect)
{
	if (!proj->is_door)
		return (0);
	proj->target = info->door;
	proj->percent_x = (double)(100 - proj->door->visible) / 100 \
						+ (proj->cur[vect] - floor(proj->cur[vect]));
	if (proj->percent_x >= 1)
		proj->percent_x = 0.9999;
	proj->percent_x = floor(proj->percent_x \
			* (double)proj->target.texture[proj->target.numtext].width);
	return (1);
}
