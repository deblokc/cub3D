/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getwalls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <bdetune@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:43:22 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/13 15:17:18 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		handle_exit(info, proj);
		proj->cur[1] += 1;
		if (proj->v[1] < 0)
			proj->cur[1] -= 2;
	}
	else
	{
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1'
				|| is_on_door(info, proj, 2))
			return (draw_wall(info, proj, 2));
		handle_exit(info, proj);
		proj->cur[0] += 1;
		if (proj->v[0] < 0)
			proj->cur[0] -= 2;
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

static int	angled_view(t_info *info, t_proj *proj, int side)
{
	if (!side)
	{
		proj->cur[1] = proj->delta[0] * proj->v[1] + proj->prev[1];
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1'
			|| is_in_corner(info, proj->cur, proj->v, 2)
			|| is_on_door(info, proj, 2))
			return (draw_wall(info, proj, 2));
		handle_exit(info, proj);
	}
	else
	{
		proj->cur[0] = proj->delta[1] * proj->v[0] + proj->prev[0];
		if (info->map[(int)proj->cur[1]][(int)proj->cur[0]] == '1'
			|| is_in_corner(info, proj->cur, proj->v, 1)
			|| is_on_door(info, proj, 1))
			return (draw_wall(info, proj, 1));
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
