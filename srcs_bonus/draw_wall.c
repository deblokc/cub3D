/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <bdetune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:43:30 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/13 11:27:27 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_strip_origin(t_info *info, t_proj *proj, int hit)
{
	if (hit == 1)
	{
		if (proj->is_door)
		{
			proj->target = info->door;
			proj->percent_x = (double)(100 - proj->door->visible) / 100 + (proj->cur[0] - floor(proj->cur[0]));
		}		
		else
		{
			proj->percent_x = (proj->cur[0] - floor(proj->cur[0])) / 1;
			proj->target = info->no;
			if (proj->v[1] > 0)
			{
				proj->percent_x = 1 - proj->percent_x;
				proj->target = info->so;
			}
		}
	}
	else
	{
		if (proj->is_door)
		{
			proj->target = info->door;
			proj->percent_x = (double)(100 - proj->door->visible) / 100 + (proj->cur[1] - floor(proj->cur[1]));
		}
		else
		{
			proj->percent_x = (proj->cur[1] - floor(proj->cur[1])) / 1;
			proj->target = info->ea;
			if (proj->v[0] < 0)
			{
				proj->percent_x = 1 - proj->percent_x;
				proj->target = info->we;
			}
		}
	}
	if (proj->percent_x >= 1)
		proj->percent_x = 0.9999;
	proj->percent_x = floor(proj->percent_x * (double)proj->target.texture[proj->target.numtext].width);
}

static void	init_strip(t_info *info, t_proj *proj)
{
	proj->start_pixel = (int)floor((((double)HEIGHT - 1) / 2) \
			- ((double)proj->wall_height / 2));
	proj->end_pixel = proj->start_pixel + proj->wall_height - 1;
	proj->dst = info->img[info->current_img].addr + proj->x \
				* (info->img[info->current_img].bits_per_pixel / 8);
	proj->origin = proj->target.texture[proj->target.numtext].addr +(int)proj->percent_x \
				* (proj->target.texture[proj->target.numtext].bits_per_pixel / 8);
	proj->step = ((double)1 / (double)proj->wall_height) \
				* (double)(proj->target.texture[proj->target.numtext].height);
}

static void	ceiling_and_floor(t_info *info, t_proj *proj, int *it, char type)
{
	if (type == 'c')
	{
		while (*it < HEIGHT && *it < proj->start_pixel)
		{
			*(unsigned int *)proj->dst = info->c;
			proj->dst += info->img[info->current_img].line_length;
			*it += 1;
		}
	}
	else
	{
		while (*it < HEIGHT)
		{
			*(unsigned int *)proj->dst = info->f;
			proj->dst += info->img[info->current_img].line_length;
			*it += 1;
		}
	}
}

static void	draw_exit(t_info *info, t_proj *proj)
{
	int				it;
	double			current;
	int				percent_y;
	unsigned int	val;

	proj->dst = info->img[info->current_img].addr + proj->x \
				* (info->img[info->current_img].bits_per_pixel / 8);
	proj->origin = info->exit.texture[info->exit.numtext].addr +(int)proj->exit_percent_x \
				* (info->exit.texture[info->exit.numtext].bits_per_pixel / 8);
	if (proj->exit_st_px < 0)
	{
		it = 0;
		current = (double)(it - proj->exit_st_px) * proj->exit_step;
	}
	else
	{
		it = proj->exit_st_px;
		current = 0;
	}
	proj->dst += info->img[info->current_img].line_length * it;
	while (it < HEIGHT && it <= proj->exit_end_px)
	{
		percent_y = (int)current;
		if (percent_y == info->exit.texture[info->exit.numtext].height)
			percent_y = info->exit.texture[info->exit.numtext].height - 1;
		val = *(unsigned int *)(proj->origin \
				+ (int)percent_y * info->exit.texture[info->exit.numtext].line_length);
		if (!(val >> 24))
			*(unsigned int *)proj->dst = val;
		proj->dst += info->img[info->current_img].line_length;
		current += proj->exit_step;
		it++;
	}
}

static void	draw_strip(t_info *info, t_proj *proj, int hit)
{
	int				it;
	double			current;
	int				percent_y;

	get_strip_origin(info, proj, hit);
	init_strip(info, proj);
	it = 0;
	ceiling_and_floor(info, proj, &it, 'c');
	current = (double)(it - proj->start_pixel) * proj->step;
	while (it < HEIGHT && it <= proj->end_pixel)
	{
		percent_y = (int)current;
		if (percent_y == proj->target.texture[proj->target.numtext].height)
			percent_y = proj->target.texture[proj->target.numtext].height - 1;
		*(unsigned int *)proj->dst = *(unsigned int *)(proj->origin \
				+ (int)percent_y * proj->target.texture[proj->target.numtext].line_length);
		proj->dst += info->img[info->current_img].line_length;
		current += proj->step;
		it++;
	}
	ceiling_and_floor(info, proj, &it, 'f');
	if (proj->has_exit)
		draw_exit(info, proj);
}

int	draw_wall(t_info *info, t_proj *proj, int hit)
{
	double	distance0;
	double	distance1;
	double	wall_ratio;

	if (fabs(proj->cur[0] - info->player.x) < 0.0001)
		distance0 = fabs(proj->cur[1] - info->player.y);
	else if (fabs(proj->cur[1] - info->player.y) < 0.0001)
		distance0 = fabs(proj->cur[0] - info->player.x);
	else
		distance0 = hypot(fabs(proj->cur[0] - info->player.x), \
				fabs(proj->cur[1] - info->player.y));
	if (fabs(proj->v[0]) < 0.0001)
		distance1 = fabs(proj->v[1]);
	else if (fabs(proj->v[1]) < 0.0001)
		distance1 = fabs(proj->v[0]);
	else
		distance1 = hypot(fabs(proj->v[0]), fabs(proj->v[1]));
	wall_ratio = distance1 / distance0;
	proj->wall_height = (int)round(wall_ratio * ((double)WIDTH / 2));
	if (!proj->is_door)
		hit = check_view_integrity(info, proj->cur, proj->v, hit);
	draw_strip(info, proj, hit);
	return (hit);
}
