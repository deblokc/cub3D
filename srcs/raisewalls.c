/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raisewalls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:33:24 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/06 13:16:23 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_strip(t_info *info, int hit, double v[2], int i, int wall_height, double cur[2])
{
	int				it;
	char			*dst;
	char			*origin;
	double			percent_x;
	double			percent_y;
	int				tot_size;
	t_texture		target;
	int				start_pixel;
	int				end_pixel;

	if (hit == 1)
	{
		if (v[1] < 0)
		{
			if (info->map[(int)floor(cur[1] + 1)][(int)floor(cur[0])] == '1')
				hit = 2;
		}
		else
		{
			if (info->map[(int)floor(cur[1] - 1)][(int)floor(cur[0])] == '1')
				hit = 2;
		}
	}
	else
	{
		if (v[0] < 0)
		{
			if (info->map[(int)floor(cur[1])][(int)floor(cur[0] + 1)] == '1')
			{
				hit = 1;
/*				if ((ceil(cur[0]) - cur[0]) < 0.0001 && (ceil(cur[1]) - cur[1]) < 0.0001 && info->map[(int)floor(cur[1] - 1)][(int)floor(cur[0])] == '1')
					cur[0] = ceil(cur[0]);
				else if ((ceil(cur[0]) - cur[0]) < 0.0001 && (cur[1] - floor(cur[1])) < 0.0001 && info->map[(int)floor(cur[1] - 1)][(int)floor(cur[0])] == '1')
					cur[0] = ceil(cur[0]);*/
			}
		}
		else
		{
			if (info->map[(int)floor(cur[1])][(int)floor(cur[0] - 1)] == '1')
			{
				hit = 1;
/*				if ((cur[0] - floor(cur[0])) < 0.0001 && (ceil(cur[1]) - cur[1]) < 0.0001 && info->map[(int)floor(cur[1] + 1)][(int)floor(cur[0])] == '1')
					cur[0] = floor(cur[0]) - 0.0001;
				else if ((cur[0] - floor(cur[0])) < 0.0001 && (cur[1] - floor(cur[1])) < 0.0001 && info->map[(int)floor(cur[1] - 1)][(int)floor(cur[0])] == '1')
					cur[0] = floor(cur[0]) - 0.0001;*/
			}
		}
	}
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
	dst = info->img[info->current_img].addr + i * (info->img[info->current_img].bits_per_pixel / 8) - info->img[info->current_img].line_length;
	origin = target.texture.addr +(int)percent_x * (target.texture.bits_per_pixel / 8);
	it = 0;
	while (it < HEIGHT)
	{
		dst += info->img[info->current_img].line_length;
		if (it < start_pixel)
			*(unsigned int *)dst = info->c;
		else if (it > end_pixel)
			*(unsigned int *)dst = info->f;
		else
		{
			percent_y = round(((double)(it - start_pixel) / (double)tot_size) * (double)(target.height - 1));
			*(unsigned int *)dst = *(unsigned int *)(origin + (int)percent_y * target.texture.line_length);
		}
		it++;
	}
}

int	draw_wall(t_info *info, double cur[2], int hit, double v[2], int i)
{
	double	distance0;
	double	distance1;
	double	wall_ratio;
	int		wall_height;

	if (fabs(cur[0] - info->player.x) < 0.0001)
		distance0 = fabs(cur[1] - info->player.y);
	else if (fabs(cur[1] - info->player.y) < 0.0001)
		distance0 = fabs(cur[0] - info->player.x);
	else
		distance0 = hypot(fabs(cur[0] - info->player.x), fabs(cur[1] - info->player.y));
	if (fabs(v[0]) < 0.0001)
		distance1 = fabs(v[1]);
	else if (fabs(v[1]) < 0.0001)
		distance1 = fabs(v[0]);
	else
		distance1 = hypot(fabs(v[0]), fabs(v[1]));
	wall_ratio = distance1 / distance0;
	wall_height = (int)round(wall_ratio * ((double)WIDTH / 2));
	draw_strip(info, hit, v, i, wall_height, cur);
	return (hit);
}

void	get_next_edge(double v[2], double delta[2], double cur[2], int fixed)
{
	double	tmp[2];

	if (fixed == 0)
	{
		if (v[0] < 0)
			tmp[0] = cur[0] - 1;
		else
			tmp[0] = cur[0] + 1;
		delta[0] = fabs(tmp[0] - cur[0]) / fabs(v[0]);
		if (v[1] < 0)
			tmp[1] = floor(cur[1]) - 0.0001;
		else
			tmp[1] = ceil(cur[1]);
		delta[1] = fabs(tmp[1] - cur[1]) / fabs(v[1]);
		if (fabs((double)delta[1]) < 0.0001)
			tmp[1] += 0.0001;
		delta[1] = fabs(tmp[1] - cur[1]) / fabs(v[1]);
	}
	else
	{
		if (v[1] < 0)
			tmp[1] = cur[1] - 1;
		else
			tmp[1] = cur[1] + 1;
		delta[1] = fabs(tmp[1] - cur[1]) / fabs(v[1]);
		if (v[0] < 0)
			tmp[0] = floor(cur[0]) - 0.0001;
		else
			tmp[0] = ceil(cur[0]);
		delta[0] = fabs(tmp[0] - cur[0]) / fabs(v[0]);
		if (fabs((double)delta[0]) < 0.0001)
			tmp[0] += 0.0001;
		delta[0] = fabs(tmp[0] - cur[0]) / fabs(v[0]);
	}
	cur[0] = tmp[0];
	cur[1] = tmp[1];
}

int	straight_line(t_info *info, double cur[2], double v[2], int i)
{
	if (fabs(v[0]) < 0.0001)
	{
		if (info->map[(int)cur[1]][(int)cur[0]] == '1')
			return (draw_wall(info, cur, 1, v, i));
		else
		{
			if (v[1] < 0)
				cur[1] -= 1;
			else
				cur[1] += 1;
		}
	}
	else
	{
		if (info->map[(int)cur[1]][(int)cur[0]] == '1')
			return (draw_wall(info, cur, 2, v, i));
		else
		{
			if (v[0] < 0)
				cur[0] -= 1;
			else
				cur[0] += 1;
		}
	}
	return (0);
}

void	get_walls(t_info *info, double v[2], double delta[2], double cur[2], int i)
{
	double	prev[2];
	int		hit;

	hit = 0;
	prev[0] = info->player.x;
	prev[1] = info->player.y;
	while (!hit)
	{
		if (fabs(v[0]) < 0.0001 || fabs(v[1]) < 0.0001)
			hit = straight_line(info, cur, v, i);
		else
		{
			if (fabs(delta[0] - delta[1]) < 0.0001 || delta[0] < delta[1])
			{
				cur[1] = delta[0] * v[1] + prev[1];
				if (info->map[(int)cur[1]][(int)cur[0]] == '1')
					hit = draw_wall(info, cur, 2, v, i);
				else
				{
					prev[0] = cur[0];
					prev[1] = cur[1];
					get_next_edge(v, delta, cur, 0);
				}
			}
			else
			{
				cur[0] = delta[1] * v[0] + prev[0];
				if (info->map[(int)cur[1]][(int)cur[0]] == '1')
					hit = draw_wall(info, cur, 1, v, i);
				else
				{
					prev[0] = cur[0];
					prev[1] = cur[1];
					get_next_edge(v, delta, cur, 1);
				}
			}
		}
	}
}

void	init_search(t_info *info, double v[2], int i)
{
	double	cur[2];
	double	delta[2];

	cur[0] = info->player.x;
	if (v[0] < -0.0001)
	{
		cur[0] = floor(info->player.x) - 0.0001;
		delta[0] = fabs(info->player.x - cur[0]) / fabs(v[0]);
	}
	else if (v[0] > 0.0001)
	{
		cur[0] = ceil(info->player.x);
		delta[0] = fabs(cur[0] - info->player.x) / fabs(v[0]);
	}
	cur[1] = info->player.y;
	if (v[1] < -0.0001)
	{
		cur[1] = floor(info->player.y) - 0.0001;
		delta[1] = fabs(info->player.y - cur[1]) / fabs(v[1]);
	}
	else if (v[1] > 0.0001)
	{
		cur[1] = ceil(info->player.y);
		delta[1] = fabs(cur[1] - info->player.y) / fabs(v[1]);
	}
	get_walls(info, v, delta, cur, i);
}

void	get_projection_screen(t_info *info, double projection_screen[4])
{
	projection_screen[0] = info->player.angle + (M_PI / 4);
	projection_screen[1] = (-sin(projection_screen[0])) * ((double)PROJ_PLANE_DIST / cos(M_PI / 4)) + info->player.y;
	projection_screen[0] = cos(projection_screen[0]) * ((double)PROJ_PLANE_DIST / cos(M_PI / 4)) + info->player.x;
	projection_screen[2] = info->player.angle - (M_PI / 4);
	projection_screen[3] = (-sin(projection_screen[2])) * ((double)PROJ_PLANE_DIST / cos(M_PI / 4)) + info->player.y;
	projection_screen[2] = cos(projection_screen[2]) * ((double)PROJ_PLANE_DIST / cos(M_PI / 4)) + info->player.x;
}

void	get_director_vector(double projection_screen[4], double director_vector[2])
{
	director_vector[0] = (projection_screen[2] - projection_screen[0]) / (double)(WIDTH - 1);
	director_vector[1] = (projection_screen[3] - projection_screen[1]) / (double)(WIDTH - 1);
}

void	raisewalls(t_info *info)
{
	double	projection_screen[4];
	double	v[2];
	int		i;
	double	director_vector[2];

	if (fabs(info->player.angle + M_PI / 2) < 0.0001)
		info->player.angle = 3 * M_PI * 2;
	else if (fabs(info->player.angle) < 0.0001)
		info->player.angle = 2 * M_PI;
	get_projection_screen(info, projection_screen);
	get_director_vector(projection_screen, director_vector);
	i = 0;
	while (i < WIDTH)
	{
		v[0] = (projection_screen[0] + director_vector[0] * i) - info->player.x;
		v[1] = (projection_screen[1] + director_vector[1] * i) - info->player.y;
		init_search(info, v, i);
		i++;
	}
}
