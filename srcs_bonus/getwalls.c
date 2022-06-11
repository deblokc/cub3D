/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getwalls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <bdetune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:43:22 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/11 13:22:08 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_exit(t_info *info, t_proj *proj)
{
	double	coords[2];
	double	coeff;
	double	angle;
	double	current_distance;

	if (!proj->exit_distance)
	{
		proj->exit_center[0] = floor(proj->cur[0]) + 0.5;
		proj->exit_center[1] = floor(proj->cur[1]) + 0.5;
		proj->exit_distance = distance(info->player.x, info->player.y, proj->exit_center[0], proj->exit_center[1]);
		proj->exit_v[0] = -(proj->exit_center[1] - info->player.y);
		proj->exit_v[1] = proj->exit_center[0] - info->player.x;
		coeff = sqrt(pow(0.5, 2) / (pow(proj->exit_v[0], 2) + pow(proj->exit_v[1], 2)));
		proj->exit_ends[0] = coeff * proj->exit_v[0] + proj->exit_center[0];
		proj->exit_ends[1] = coeff *  proj->exit_v[1] + proj->exit_center[1];
		proj->exit_ends[2] = -coeff * proj->exit_v[0] + proj->exit_center[0];
		proj->exit_ends[3] = -coeff * proj->exit_v[1] + proj->exit_center[1];
		angle = vector_angle(proj->exit_v, proj->v);
		if (fabs(angle) < 0.0001)
			current_distance = proj->exit_distance;
		else
			current_distance = proj->exit_distance / cos(angle);
		proj->exit_height = (distance(0, 0, proj->v[0], proj->v[1]) / current_distance) * ((double)WIDTH / 2);
		proj->exit_st_px = (int)floor((((double)HEIGHT - 1) / 2) \
			- ((double)proj->exit_height / 2));
		proj->exit_end_px = proj->exit_st_px + proj->exit_height - 1;
		proj->exit_step = ((double)1 / (double)proj->exit_height) \
				* (double)(info->exit.texture[info->exit.numtext].height);
	}
	angle = vector_angle(proj->exit_v, proj->v);
	if (fabs(angle) < 0.0001)
		current_distance = proj->exit_distance;
	else
		current_distance = proj->exit_distance / cos(angle);
	coeff = sqrt(pow(current_distance, 2) / (pow(proj->v[0], 2) + pow(proj->v[1], 2)));
	coords[0] = info->player.x + proj->v[0] * coeff;
	coords[1] = info->player.y + proj->v[1] * coeff;
	if (distance(coords[0], coords[1], proj->exit_center[0], proj->exit_center[1]) > 0.5)
		return ;
	proj->has_exit = 1;
	proj->exit_percent_x = distance(proj->exit_ends[0], proj->exit_ends[1], coords[0], coords[1]);
	if (proj->exit_percent_x >= 1)
		proj->exit_percent_x = 0.9999;
	proj->exit_percent_x = floor(proj->exit_percent_x * info->exit.texture[info->exit.numtext].width);
}

static void	get_next_edge(t_proj *proj, int fixed)
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

static int	straight_line(t_info *info, t_proj *proj)
{
	if (fabs(proj->v[0]) < 0.0001)
	{
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1'
				|| is_on_door(info, proj, 1))
			return (draw_wall(info, proj, 1));
		else
		{
			if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == 'X')
				handle_exit(info, proj);
			proj->cur[1] += 1;
			if (proj->v[1] < 0)
				proj->cur[1] -= 2;
		}
	}
	else
	{
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1'
				|| is_on_door(info, proj, 2))
			return (draw_wall(info, proj, 2));
		else
		{
			if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == 'X')
				handle_exit(info, proj);
			proj->cur[0] += 1;
			if (proj->v[0] < 0)
				proj->cur[0] -= 2;
		}
	}
	return (0);
}

static int	is_in_corner(t_info *info, double cur[2], double v[2], int hit)
{
	int	c[2];

	c[0] = (int)cur[0];
	c[1] = (int)cur[1];
	if (hit == 1)
	{
		if (v[1] < 0 && info->map[(c[1] + 1)][c[0]] == '1'
			&& ((v[0] <= 0 && info->map[c[1]][(c[0] + 1)] == '1')
				|| (v[0] >= 0 && info->map[c[1]][(c[0] - 1)] == '1')))
			return (1);
		else if (v[1] > 0 && info->map[(c[1] - 1)][c[0]] == '1'
			&& ((v[0] <= 0 && info->map[c[1]][(c[0] + 1)] == '1')
				|| (v[0] >= 0 && info->map[c[1]][(c[0] - 1)] == '1')))
			return (1);
		return (0);
	}
	if (v[0] < 0 && info->map[c[1]][(c[0] + 1)] == '1'
		&& ((v[1] <= 0 && info->map[(c[1] + 1)][c[0]] == '1')
			|| (v[1] >= 0 && info->map[(c[1] - 1)][c[0]] == '1')))
		return (1);
	else if (v[0] > 0 && info->map[c[1]][(c[0] - 1)] == '1'
		&& ((v[1] <= 0 && info->map[(c[1] + 1)][c[0]] == '1')
			|| (v[1] >= 0 && info->map[(c[1] - 1)][c[0]] == '1')))
		return (1);
	return (0);
}

int	is_on_door(t_info *info, t_proj *proj, int hit)
{
	double	visible[2];
	double	next[2];
	int		c[2];
	
	c[0] = (int)proj->cur[0];
	c[1] = (int)proj->cur[1];
	if (info->map[c[1]][c[0]] != '2')
		return (0);
	proj->door = find_door(info, c);
	if (!proj->door)
		return (0);
	if (hit == 1)
	{
		visible[0] = c[0];
		visible[1] = visible[0] + (double)proj->door->visible / 100;
		if (proj->cur[0] >= visible[0] && proj->cur[0] <= visible[1])
		{
			proj->is_door = 1;
			return (1);
		}
		if (proj->v[1] < 0)
		{
			next[1] = (double)c[1];
			next[0] = (fabs(next[1] - proj->cur[1]) / fabs(proj->v[1])) * proj->v[0] + proj->cur[0];
		}
		else
		{
			next[1] = (double)c[1] + 0.9999;
			next[0] = (fabs(next[1] - proj->cur[1]) / fabs(proj->v[1])) * proj->v[0] + proj->cur[0];
		}
		if (next[0] >= visible[0] && next[0] <= visible[1])
		{
			proj->cur[0] = next[0];
			proj->cur[1] = next[1];
			proj->is_door = 1;
			return (1);
		}
		return (0);
	}
	visible[0] = c[1];
	visible[1] = visible[0] + (double)proj->door->visible / 100;
	if (proj->cur[1] >= visible[0] && proj->cur[1] <= visible[1])
	{
		proj->is_door = 1;
		return (1);
	}
	if (proj->v[0] < 0)
	{
		next[0] = (double)c[0];
		next[1] = (fabs(next[0] - proj->cur[0]) / fabs(proj->v[0])) * proj->v[1] + proj->cur[1];
	}
	else
	{
		next[0] = (double)c[0] + 0.9999;
		next[1] = (fabs(next[0] - proj->cur[0]) / fabs(proj->v[0])) * proj->v[1] + proj->cur[1];
	}
	if (next[1] >= visible[0] && next[1] <= visible[1])
	{
		proj->cur[0] = next[0];
		proj->cur[1] = next[1];
		proj->is_door = 1;
		return (1);
	}
	return (0);
}

static int	angled_view(t_info *info, t_proj *proj, int side)
{
	if (!side)
	{
		proj->cur[1] = proj->delta[0] * proj->v[1] + proj->prev[1];
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1'
			|| is_in_corner(info, proj->cur, proj->v, 2)
			|| is_on_door(info, proj, 2))
			return (draw_wall(info, proj, 2));
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == 'X')
			handle_exit(info, proj);
	}
	else
	{
		proj->cur[0] = proj->delta[1] * proj->v[0] + proj->prev[0];
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1'
			|| is_in_corner(info, proj->cur, proj->v, 1)
			|| is_on_door(info, proj, 1))
			return (draw_wall(info, proj, 1));
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == 'X')
			handle_exit(info, proj);
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
