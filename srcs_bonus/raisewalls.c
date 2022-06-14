/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raisewalls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdetune <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:33:24 by bdetune           #+#    #+#             */
/*   Updated: 2022/06/11 11:08:01 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_search(t_info *info, t_proj *proj)
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

static void	get_proj_screen(t_info *info, t_proj *proj)
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

static void	get_dir_v(t_info *info, t_proj *proj)
{
	proj->dir_v[0] = (proj->proj_screen[2] - proj->proj_screen[0]) \
					/ (double)(info->width - 1);
	proj->dir_v[1] = (proj->proj_screen[3] - proj->proj_screen[1]) \
					/ (double)(info->width - 1);
}

void	raisewalls(t_info *info)
{
	t_proj	proj;

	if (fabs(info->player.angle + M_PI / 2) < 0.0001)
		info->player.angle = 3 * M_PI * 2;
	else if (fabs(info->player.angle) < 0.0001)
		info->player.angle = 2 * M_PI;
	get_proj_screen(info, &proj);
	get_dir_v(info, &proj);
	proj.exit_distance = 0;
	proj.x = 0;
	while (proj.x < info->width)
	{
		proj.is_door = 0;
		proj.has_exit = 0;
		proj.v[0] = (proj.proj_screen[0] + proj.dir_v[0] * proj.x) \
					- info->player.x;
		proj.v[1] = (proj.proj_screen[1] + proj.dir_v[1] * proj.x) \
					- info->player.y;
		init_search(info, &proj);
		proj.x += 1;
	}
}
