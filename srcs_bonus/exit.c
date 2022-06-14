/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:17:15 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/13 15:39:53 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_exit(t_info *info, t_proj *proj)
{
	double	coeff;

	proj->exit_center[0] = floor(proj->cur[0]) + 0.5;
	proj->exit_center[1] = floor(proj->cur[1]) + 0.5;
	proj->exit_distance = distance(info->player.x, info->player.y, \
			proj->exit_center[0], proj->exit_center[1]);
	proj->exit_v[0] = -(proj->exit_center[1] - info->player.y);
	proj->exit_v[1] = proj->exit_center[0] - info->player.x;
	coeff = sqrt(pow(0.5, 2) / (pow(proj->exit_v[0], 2) \
				+ pow(proj->exit_v[1], 2)));
	proj->exit_ends[0] = coeff * proj->exit_v[0] + proj->exit_center[0];
	proj->exit_ends[1] = coeff * proj->exit_v[1] + proj->exit_center[1];
	proj->exit_ends[2] = -coeff * proj->exit_v[0] + proj->exit_center[0];
	proj->exit_ends[3] = -coeff * proj->exit_v[1] + proj->exit_center[1];
	proj->exit_v[0] = proj->exit_center[0] - info->player.x;
	proj->exit_v[1] = proj->exit_center[1] - info->player.y;
}

static void	x_coords(t_info *info, t_proj *proj, double coords[2], \
			double *current_distance)
{
	double	coeff;
	double	angle;

	angle = vector_angle(proj->exit_v, proj->v);
	if (fabs(angle) < 0.0001)
		*current_distance = proj->exit_distance;
	else
		*current_distance = proj->exit_distance / cos(angle);
	coeff = sqrt(pow(*current_distance, 2) / (pow(proj->v[0], 2) \
				+ pow(proj->v[1], 2)));
	coords[0] = info->player.x + proj->v[0] * coeff;
	coords[1] = info->player.y + proj->v[1] * coeff;
}

void	handle_exit(t_info *info, t_proj *proj)
{
	double	coords[2];
	double	current_distance;

	if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] != 'X')
		return ;
	if (!proj->exit_distance)
		init_exit(info, proj);
	x_coords(info, proj, coords, &current_distance);
	if (distance(coords[0], coords[1], proj->exit_center[0], \
			proj->exit_center[1]) > 0.5)
		return ;
	proj->has_exit = 1;
	proj->exit_percent_x = distance(proj->exit_ends[0], proj->exit_ends[1], \
							coords[0], coords[1]);
	if (proj->exit_percent_x >= 1)
		proj->exit_percent_x = 0.9999;
	proj->exit_percent_x = floor(proj->exit_percent_x \
							* info->exit.texture[info->exit.numtext].width);
	proj->exit_height = (distance(0, 0, proj->v[0], proj->v[1]) \
						/ current_distance) * ((double)info->width / 2);
	proj->exit_st_px = (int)floor((((double)info->height - 1) / 2) \
			- ((double)proj->exit_height / 2));
	proj->exit_end_px = proj->exit_st_px + proj->exit_height - 1;
	proj->exit_step = ((double)1 / (double)proj->exit_height) \
			* (double)(info->exit.texture[info->exit.numtext].height);
}

static void	init_exit_draw(t_info *info, t_proj *proj, int *it, double *current)
{
	proj->dst = info->img[info->current_img].addr + proj->x \
				* (info->img[info->current_img].bits_per_pixel / 8);
	proj->origin = info->exit.texture[info->exit.numtext].addr + \
				(int)proj->exit_percent_x \
				* (info->exit.texture[info->exit.numtext].bits_per_pixel / 8);
	if (proj->exit_st_px < 0)
	{
		*it = 0;
		*current = (double)(*it - proj->exit_st_px) * proj->exit_step;
	}
	else
	{
		*it = proj->exit_st_px;
		*current = 0;
	}
	proj->dst += info->img[info->current_img].line_length * *it;
}

void	draw_exit(t_info *info, t_proj *proj)
{
	int				it;
	double			current;
	int				percent_y;
	unsigned int	val;

	init_exit_draw(info, proj, &it, &current);
	while (it < info->height && it <= proj->exit_end_px)
	{
		percent_y = (int)current;
		if (percent_y == info->exit.texture[info->exit.numtext].height)
			percent_y = info->exit.texture[info->exit.numtext].height - 1;
		val = *(unsigned int *)(proj->origin + (int)percent_y \
				* info->exit.texture[info->exit.numtext].line_length);
		if (!(val >> 24))
			*(unsigned int *)proj->dst = val;
		proj->dst += info->img[info->current_img].line_length;
		current += proj->exit_step;
		it++;
	}
}
