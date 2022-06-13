/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:20:58 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/13 15:19:22 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	closewin(t_info *info)
{
	int	i;

	i = 0;
	while (i < NB_IMG)
	{
		mlx_destroy_image(info->mlx, info->img[i].img);
		i++;
	}
	mlx_do_key_autorepeaton(info->mlx);
	freeinfo(info);
	exit(0);
}

int	iswall(t_info *info, double y, double x)
{
	t_door	*tmp;
	int		relou[2];

	if (info->map[(int)floor(y)][(int)floor(x)] == '1')
		return (1);
	relou[0] = (int)x;
	relou[1] = (int)y;
	tmp = find_door(info, relou);
	if (tmp && tmp->visible != 0)
		return (1);
	return (0);
}

void	goforwardy(t_info *info)
{
	if (sin(info->player.angle) > 0)
	{
		if (!iswall(info, (info->player.y - (sin(info->player.angle) * \
							(STEP)) - 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle) * STEP);
		else
			info->player.y = floor(info->player.y) + 0.1;
	}
	else
	{
		if (!iswall(info, (info->player.y - (sin(info->player.angle) * \
							(STEP)) + 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle) * STEP);
		else
			info->player.y = ceil(info->player.y) - 0.1;
	}
}

void	goforwardx(t_info *info, double oldy)
{
	if (cos(info->player.angle) > 0)
	{
		if (!iswall(info, oldy, (info->player.x + cos(info->player.angle) * \
						(STEP) + 0.1)))
			info->player.x += (cos(info->player.angle) * STEP);
		else
			info->player.x = ceil(info->player.x) - 0.1;
	}
	else
	{
		if (!iswall(info, oldy, (info->player.x + cos(info->player.angle) * \
						(STEP) - 0.1)))
			info->player.x += (cos(info->player.angle) * STEP);
		else
			info->player.x = floor(info->player.x) + 0.1;
	}
}

void	goforward(t_info *info)
{
	double	oldy;
	double	oldx;

	oldy = info->player.y;
	oldx = info->player.x;
	goforwardy(info);
	goforwardx(info, oldy);
	if (iswall(info, info->player.y, info->player.x))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
}
