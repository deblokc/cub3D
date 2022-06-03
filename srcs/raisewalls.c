/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raisewalls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:33:24 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/03 19:15:32 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_strip(t_info *info, int hit, double v[2], int i, int wall_height, double cur[2])
{
	int				it;
	char			*dst;
	char			*origin;
//	unsigned int	val;
	double			percent_x;
	double			percent_y;
	t_texture		target;
	int				start_pixel;
	int				end_pixel;

	if (hit == 1)
	{
		if (v[1] < 0)
			target = info->no;
		else
			target = info->so;
		percent_x = (cur[0] - floor(cur[0])) / 0.9999;
		if (percent_x > 1)
			percent_x = 1;
		percent_x = round(percent_x * (double)(target.width - 1));
	}
	else
	{
		if (v[0] < 0)
			target = info->we;
		else
			target = info->ea;
		percent_x = (cur[1] - floor(cur[1])) / 0.9999;
		if (percent_x > 1)
			percent_x = 1;
		percent_x = round(percent_x * (double)(target.width - 1));
	}
	start_pixel = (int)ceil((((double)HEIGHT - 1) / 2) - ((double)wall_height / 2));
	end_pixel = (int)ceil((((double)HEIGHT - 1) / 2) + ((double)wall_height / 2));
	it = start_pixel;
	while (it < (end_pixel + 1))
	{
		if (it < 0 || it >= HEIGHT)
		{
			it++;
			continue ;
		}
		dst = info->img.addr + (it * info->img.line_length + i * (info->img.bits_per_pixel / 8));
		percent_y = (double)(it - start_pixel) / (double)(end_pixel - start_pixel);
		if (percent_y > 1)
			percent_y = 1;
		percent_y = round(percent_y * (double)(target.height - 1));
		origin = target.texture.addr + ((int)percent_y * target.texture.line_length + (int)percent_x * (target.texture.bits_per_pixel / 8));
		*(unsigned int *)dst = *(unsigned *)origin;
		it++;
	}
}

int	draw_wall(t_info *info, double cur[2], int hit, double v[2], int i)
{
	double	distance0;
	double	distance1;
	double	wall_ratio;
	int		wall_height;

	distance0 = hypot(fabs(cur[0] - info->player.x), fabs(cur[1] - info->player.y));
	if (fabs(v[0]) < 0.0001)
		distance1 = v[1];
	else if (fabs(v[1]) < 0.0001)
		distance1 = v[0];
	else
		distance1 = hypot(fabs(v[0]), fabs(v[1]));
	wall_ratio = distance1 / distance0;
	wall_height = (int)round(wall_ratio * ((double)WIDTH / 2));
//	printf("found intersection at %.4f; %.4f\n", cur[0], cur[1]);
//	printf("Hit on %c\n", hit==1?'y':'x');
//	printf("Ratio: %.8f\n", wall_ratio);
//	printf("Wall height: %d\n", wall_height);
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
	if (fabs(v[0]) < 0.000001)
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

void get_walls(t_info *info, double v[2], double delta[2], double cur[2], int i)
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
	if (v[0] < -0.000001)
	{
		cur[0] = floor(info->player.x) - 0.0001;
		delta[0] = fabs(info->player.x - cur[0]) / fabs(v[0]);
	}
	else if (v[0] > 0.000001)
	{
		cur[0] = ceil(info->player.x);
		delta[0] = fabs(cur[0] - info->player.x) / fabs(v[0]);
	}
	cur[1] = info->player.y;
	if (v[1] < -0.000001)
	{
		cur[1] = floor(info->player.y) - 0.0001;
		delta[1] = fabs(info->player.y - cur[1]) / fabs(v[1]);
	}
	else if (v[1] > 0.000001)
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

void get_director_vector(double projection_screen[4], double director_vector[2])
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

	if (fabs(info->player.angle + M_PI / 2) < 0.00001)
		info->player.angle = 3 * M_PI * 2;
	else if (fabs(info->player.angle) < 0.00001)
		info->player.angle = 2 * M_PI;
	get_projection_screen(info, projection_screen);
	get_director_vector(projection_screen, director_vector);
	printf("Player position: %.4f ; %.4f\n", info->player.x, info->player.y);
	//printf("Player position: %.4f ; %.4f\nProjection screen 0: %.4f ; %.4f\nProjection screen 1: %.4f ; %.4f\n", info->player.x, info->player.y, projection_screen[0], projection_screen[1], projection_screen[2], projection_screen[3]);
//	printf("director vector: %.8f ; %.8f\n", director_vector[0], director_vector[1]);
	i = 0;
	while (i < WIDTH)
	{
		v[0] = (projection_screen[0] + director_vector[0] * i) - info->player.x;
		v[1] = (projection_screen[1] + director_vector[1] * i) - info->player.y;
//		printf("search_vector: %.8f ; %.8f\n", v[0], v[1]);
		init_search(info, v, i);
		i++;
	}
}
