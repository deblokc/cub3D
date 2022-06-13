/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendoor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:06:30 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/13 19:07:04 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	toggle_door(t_info *info)
{
	t_proj	proj;
	int		coords[2];

	proj.door = NULL;
	proj.v[0] = cos(info->player.angle);
	proj.v[1] = -sin(info->player.angle);
	proj.cur[0] = info->player.x;
	proj.delta[0] = 10;
	if (proj.v[0] < -0.0001 || proj.v[0] > 0.0001)
	{
		if (proj.v[0] < -0.0001)
			proj.cur[0] = floor(info->player.x) - 0.0001;
		else
			proj.cur[0] = ceil(info->player.x);
		proj.delta[0] = fabs(proj.cur[0] - info->player.x) / fabs(proj.v[0]);
	}
	proj.cur[1] = info->player.y;
	proj.delta[1] = 10;
	if (proj.v[1] < -0.0001 || proj.v[1] > 0.0001)
	{
		if (proj.v[1] < -0.0001)
			proj.cur[1] = floor(info->player.y) - 0.0001;
		else
			proj.cur[1] = ceil(info->player.y);
		proj.delta[1] = fabs(proj.cur[1] - info->player.y) / fabs(proj.v[1]);
	}
	if (proj.delta[0] < proj.delta[1])
		proj.cur[1] = proj.delta[0] * proj.v[1] + info->player.y;
	else
		proj.cur[0] = proj.delta[1] * proj.v[0] + info->player.x;
	while (distance(proj.cur[0], proj.cur[1], \
				info->player.x, info->player.y) <= 1)
	{
		coords[0] = (int)proj.cur[0];
		coords[1] = (int)proj.cur[1];
		if (info->map[coords[1]][coords[0]] == '1')
			return ;
		if (info->map[coords[1]][coords[0]] == '2')
		{
			proj.door = find_door(info, coords);
			break ;
		}
		proj.cur[0] += 0.1 * proj.v[0];
		proj.cur[1] += 0.1 * proj.v[1];
	}
	if (proj.door)
	{
		proj.door->opened_time = 0;
		if (proj.door->motion == 0 && proj.door->visible == 100)
			proj.door->motion = -1;
		else if (proj.door->motion == 0 && proj.door->visible == 0)
			proj.door->motion = 1;
		else if (proj.door->motion == 1)
			proj.door->motion = -1;
		else
			proj.door->motion = 1;
	}
}

void	handle_doors(t_info *info)
{
	t_door	*current;

	current = info->doors;
	while (current)
	{
		if ((int)info->player.x == current->x \
				&& (int)info->player.y == current->y)
		{
			current->opened_time = 0;
			current->visible = 0;
			current->motion = 0;
		}
		else
		{
			if (current->opened_time == 60)
				current->motion = 1;
			if (current->motion == -1)
				current->visible -= 2;
			else if (current->motion == 1)
				current->visible += 2;
			else if (current->visible == 0 && current->motion == 0)
				current->opened_time += 1;
			if (current->visible < 0)
			{
				current->visible = 0;
				current->motion = 0;
				current->opened_time = 1;
			}
			else if (current->visible > 100)
			{
				current->visible = 100;
				current->motion = 0;
				current->opened_time = 0;
			}
		}
		current = current->next;
	}
}
