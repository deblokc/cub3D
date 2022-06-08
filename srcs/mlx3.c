/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:23:34 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/08 16:28:57 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	gobacky(t_info *info)
{
	if (sin(info->player.angle) < 0)
	{
		if (!iswall(info, (info->player.y + (sin(info->player.angle) * \
							(STEP)) - 0.1), info->player.x))
			info->player.y += (sin(info->player.angle) * STEP);
		else
			info->player.y = floor(info->player.y) + 0.1;
	}
	else
	{
		if (!iswall(info, (info->player.y + (sin(info->player.angle) * \
							(STEP)) + 0.1), info->player.x))
			info->player.y += (sin(info->player.angle) * STEP);
		else
			info->player.y = ceil(info->player.y) - 0.1;
	}
}

void	gobackx(t_info *info, double oldy)
{
	if (cos(info->player.angle) < 0)
	{
		if (!iswall(info, oldy, (info->player.x - cos(info->player.angle) * \
						(STEP) + 0.1)))
			info->player.x -= (cos(info->player.angle) * STEP);
		else
			info->player.x = ceil(info->player.x) - 0.1;
	}
	else
	{
		if (!iswall(info, oldy, (info->player.x - cos(info->player.angle) * \
						(STEP) - 0.1)))
			info->player.x -= (cos(info->player.angle) * STEP);
		else
			info->player.x = floor(info->player.x) + 0.1;
	}
}

void	goback(t_info *info)
{
	double	oldy;
	double	oldx;

	oldy = info->player.y;
	oldx = info->player.x;
	gobacky(info);
	gobackx(info, oldy);
	if (iswall(info, info->player.y, info->player.x))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
//	loop(info);
}

void	golefty(t_info *info)
{
	if (sin(info->player.angle + (M_PI / 2)) > 0)
	{
		if (!iswall(info, (info->player.y - (sin(info->player.angle + \
								(M_PI / 2)) * (STEP)) - 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle + (M_PI / 2)) * STEP);
		else
			info->player.y = floor(info->player.y) + 0.1;
	}
	else
	{
		if (!iswall(info, (info->player.y - (sin(info->player.angle + \
								(M_PI / 2)) * (STEP)) + 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle + (M_PI / 2)) * STEP);
		else
			info->player.y = ceil(info->player.y) - 0.1;
	}
}

void	goleftx(t_info *info, double oldy)
{
	if (cos(info->player.angle + (M_PI / 2)) > 0)
	{
		if (!iswall(info, oldy, (info->player.x + (cos(info->player.angle + \
								(M_PI / 2)) * (STEP)) + 0.1)))
			info->player.x += (cos(info->player.angle + (M_PI / 2)) * STEP);
		else
			info->player.x = ceil(info->player.x) - 0.1;
	}
	else
	{
		if (!iswall(info, oldy, (info->player.x + (cos(info->player.angle + \
								(M_PI / 2)) * (STEP)) - 0.1)))
			info->player.x += (cos(info->player.angle + (M_PI / 2)) * STEP);
		else
			info->player.x = floor(info->player.x) + 0.1;
	}
}
