/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raisewalls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:33:24 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/07 16:24:37 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_strip(t_info *info, int hit, double v[2], int i, int wall_height, double cur[2])
{
	int				it;
	double			step;
	double			current;
	char			*dst;
	char			*origin;
	double			percent_x;
	int				percent_y;
	int				tot_size;
	t_texture		target;
	int				start_pixel;
	int				end_pixel;

	if (hit == 1)
	{
		if (v[1] < 0)
		{
			target = info->no;
			percent_x = (cur[0] - floor(cur[0])) / 1;
			if (percent_x >= 1)
				percent_x = 0.9999;
			percent_x = floor(percent_x * (double)target.width);
		}
		else
		{
			target = info->so;
			percent_x = 1 - (cur[0] - floor(cur[0])) / 1;
			if (percent_x >= 1)
				percent_x = 0.9999;
			percent_x = floor(percent_x * (double)target.width);
		}
	}
	else
	{
		if (v[0] < 0)
		{
			target = info->we;
			percent_x = 1 - (cur[1] - floor(cur[1])) / 1;
			if (percent_x >= 1)
				percent_x = 0.9999;
			percent_x = floor(percent_x * (double)target.width);
		}
		else
		{
			target = info->ea;
			percent_x = (cur[1] - floor(cur[1])) / 1;
			if (percent_x >= 1)
				percent_x = 0.9999;
			percent_x = floor(percent_x * (double)target.width);
		}
	}
	start_pixel = (int)floor((((double)HEIGHT - 1) / 2) - ((double)wall_height / 2));
	end_pixel = start_pixel + wall_height - 1;
	tot_size = end_pixel - start_pixel;
	dst = info->img[info->current_img].addr + i * (info->img[info->current_img].bits_per_pixel / 8);
	origin = target.texture.addr +(int)percent_x * (target.texture.bits_per_pixel / 8);
	it = 0;
	while (it < HEIGHT && it < start_pixel)
	{
		*(unsigned int *)dst = info->c;
		dst += info->img[info->current_img].line_length;
		it++;
	}
	step = ((double)(1) / (double)tot_size) * (double)(target.height);
	current = (double)(it - start_pixel) * step;
	while (it < HEIGHT && it <= end_pixel)
	{
		percent_y = (int)current;
		if (percent_y == target.height)
			percent_y = target.height - 1;
		*(unsigned int *)dst = *(unsigned int *)(origin + (int)percent_y * target.texture.line_length);
		dst += info->img[info->current_img].line_length;
		current += step;
		it++;
	}
	while (it < HEIGHT)
	{
		*(unsigned int *)dst = info->f;
		dst += info->img[info->current_img].line_length;
		it++;
	}
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
	hit = check_view_integrity(info, proj->cur, proj->v, hit);
	draw_strip(info, hit, proj->v, proj->x, proj->wall_height, proj->cur);
	return (hit);
}

void	get_next_edge(t_proj *proj, int fixed)
{
	double	tmp[2];
	int		pendant;

	pendant = fixed ^ 1;
	if (proj->v[fixed] < 0)
		tmp[fixed] = proj->cur[fixed] - 1;
	else
		tmp[fixed] = proj->cur[fixed] + 1;
	proj->delta[fixed] = fabs(tmp[fixed] - proj->cur[fixed]) \
						/ fabs(proj->v[fixed]);
	if (proj->v[pendant] < 0)
		tmp[pendant] = floor(proj->cur[pendant]) - 0.0001;
	else
		tmp[pendant] = ceil(proj->cur[pendant]);
	proj->delta[pendant] = fabs(tmp[pendant] - proj->cur[pendant]) \
							/ fabs(proj->v[pendant]);
	if (fabs((double)proj->delta[pendant]) < 0.0001)
		tmp[pendant] += 0.0001;
	proj->delta[pendant] = fabs(tmp[pendant] - proj->cur[pendant]) \
							/ fabs(proj->v[pendant]);
	proj->cur[0] = tmp[0];
	proj->cur[1] = tmp[1];
}

int	straight_line(t_info *info, t_proj *proj)
{
	if (fabs(proj->v[0]) < 0.0001)
	{
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1')
			return (draw_wall(info, proj, 1));
		else
		{
			proj->cur[1] += 1;
			if (proj->v[1] < 0)
				proj->cur[1] -= 2;
		}
	}
	else
	{
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1')
			return (draw_wall(info, proj, 2));
		else
		{
			proj->cur[0] += 1;
			if (proj->v[0] < 0)
				proj->cur[0] -= 2;
		}
	}
	return (0);
}

int	angled_view(t_info *info, t_proj *proj, int side)
{
	if (!side)
	{
		proj->cur[1] = proj->delta[0] * proj->v[1] + proj->prev[1];
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1')
			return (draw_wall(info, proj, 2));
	}
	else
	{
		proj->cur[0] = proj->delta[1] * proj->v[0] + proj->prev[0];
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1')
			return (draw_wall(info, proj, 1));
	}
	proj->prev[0] = proj->cur[0];
	proj->prev[1] = proj->cur[1];
	get_next_edge(proj, side);
	return (0);

}

void	get_walls(t_info *info, t_proj *proj)
{
	int		hit;

	hit = 0;
	proj->prev[0] = info->player.x;
	proj->prev[1] = info->player.y;
	while (!hit)
	{
		if (fabs(proj->v[0]) < 0.0001 || fabs(proj->v[1]) < 0.0001)
			hit = straight_line(info, proj);
		else
		{
			if (fabs(proj->delta[0] - proj->delta[1]) < 0.0001
					|| proj->delta[0] < proj->delta[1])
				hit = angled_view(info, proj, 0);
			else
				hit = angled_view(info, proj, 1);
		}
	}
}

void	init_search(t_info *info, t_proj *proj)
{
	proj->cur[0] = info->player.x;
	if (proj->v[0] < -0.0001 || proj->v[0] > 0.0001)
	{
		if (proj->v[0] < -0.0001)
			proj->cur[0] = floor(info->player.x) - 0.0001;
		else
			proj->cur[0] = ceil(info->player.x);
		proj->delta[0] = fabs(proj->cur[0] - info->player.x) / fabs(proj->v[0]);
	}
	proj->cur[1] = info->player.y;
	if (proj->v[1] < -0.0001 || proj->v[1] > 0.0001)
	{
		if (proj->v[1] < -0.0001)
			proj->cur[1] = floor(info->player.y) - 0.0001;
		else
			proj->cur[1] = ceil(info->player.y);
		proj->delta[1] = fabs(proj->cur[1] - info->player.y) / fabs(proj->v[1]);
	}
	get_walls(info, proj);
}

void	get_proj_screen(t_info *info, t_proj *proj)
{
	proj->proj_screen[0] = info->player.angle + (M_PI / 4);
	proj->proj_screen[1] = (-sin(proj->proj_screen[0])) \
								*((double)PROJ_PLANE_DIST \
								/ cos(M_PI / 4)) + info->player.y;
	proj->proj_screen[0] = cos(proj->proj_screen[0]) \
								*((double)PROJ_PLANE_DIST \
								/ cos(M_PI / 4)) + info->player.x;
	proj->proj_screen[2] = info->player.angle - (M_PI / 4);
	proj->proj_screen[3] = (-sin(proj->proj_screen[2])) \
								*((double)PROJ_PLANE_DIST \
								/ cos(M_PI / 4)) + info->player.y;
	proj->proj_screen[2] = cos(proj->proj_screen[2]) \
								*((double)PROJ_PLANE_DIST \
								/ cos(M_PI / 4)) + info->player.x;
}

void	get_dir_v(t_proj *proj)
{
	proj->dir_v[0] = (proj->proj_screen[2] - proj->proj_screen[0]) \
					/ (double)(WIDTH - 1);
	proj->dir_v[1] = (proj->proj_screen[3] - proj->proj_screen[1]) \
					/ (double)(WIDTH - 1);
}

void	raisewalls(t_info *info)
{
	t_proj	proj;

	if (fabs(info->player.angle + M_PI / 2) < 0.0001)
		info->player.angle = 3 * M_PI * 2;
	else if (fabs(info->player.angle) < 0.0001)
		info->player.angle = 2 * M_PI;
	get_proj_screen(info, &proj);
	get_dir_v(&proj);
	proj.x = 0;
	while (proj.x < WIDTH)
	{
		proj.v[0] = (proj.proj_screen[0] + proj.dir_v[0] * proj.x) \
					- info->player.x;
		proj.v[1] = (proj.proj_screen[1] + proj.dir_v[1] * proj.x) \
					- info->player.y;
		init_search(info, &proj);
		proj.x += 1;
	}
}
