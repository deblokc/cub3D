/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:25:58 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/08 19:00:56 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	goleft(t_info *info)
{
	double	oldy;
	double	oldx;

	oldy = info->player.y;
	oldx = info->player.x;
	golefty(info);
	goleftx(info, oldy);
	if (iswall(info, info->player.y, info->player.x))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
}

void	gorighty(t_info *info)
{
	if (sin(info->player.angle - (M_PI / 2)) > 0)
	{
		if (!iswall(info, (info->player.y - (sin(info->player.angle - \
								(M_PI / 2)) * (STEP)) - 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle - (M_PI / 2)) * STEP);
		else
			info->player.y = floor(info->player.y) + 0.1;
	}
	else
	{
		if (!iswall(info, (info->player.y - (sin(info->player.angle - \
								(M_PI / 2)) * (STEP)) + 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle - (M_PI / 2)) * STEP);
		else
			info->player.y = ceil(info->player.y) - 0.1;
	}
}

void	gorightx(t_info *info, double oldy)
{
	if (cos(info->player.angle - (M_PI / 2)) > 0)
	{
		if (!iswall(info, oldy, (info->player.x + (cos(info->player.angle - \
								(M_PI / 2)) * (STEP)) + 0.1)))
			info->player.x += (cos(info->player.angle - (M_PI / 2)) * STEP);
		else
			info->player.x = ceil(info->player.x) - 0.1;
	}
	else
	{
		if (!iswall(info, oldy, (info->player.x + (cos(info->player.angle - \
								(M_PI / 2)) * (STEP)) - 0.1)))
			info->player.x += (cos(info->player.angle - (M_PI / 2)) * STEP);
		else
			info->player.x = floor(info->player.x) + 0.1;
	}
}

void	goright(t_info *info)
{
	double	oldy;
	double	oldx;

	oldy = info->player.y;
	oldx = info->player.x;
	gorighty(info);
	gorightx(info, oldy);
	if (iswall(info, info->player.y, info->player.x))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
}

void	turnright(t_info *info)
{
	info->player.angle -= ((5 * M_PI) / 180);
	if (info->player.angle == 0)
		info->player.angle = 2 * M_PI;
}
