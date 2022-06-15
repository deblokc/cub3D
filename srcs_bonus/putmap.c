/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:02:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/15 13:27:06 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	putplayer(t_info *info, t_img *img, int coords[2], unsigned int color)
{
	int	nexty;
	int	nextx;
	int	retx;

	retx = coords[0] - 3;
	nexty = coords[1] + 3;
	nextx = coords[0] + 3;
	coords[1] -= 3;
	while (coords[1] < nexty)
	{
		coords[0] = retx;
		while (coords[0] < nextx)
		{
			if (coords[0] > 0 && coords[0] < info->width \
					&& coords[1] > 0 && coords[1] < info->height)
				putpixel(img, coords[0], coords[1], color);
			coords[0] += 1;
		}
		coords[1] += 1;
	}
}

void	putsquare(t_info *info, t_img *img, int lst[3], unsigned int color)
{
	int		nexty;
	int		nextx;
	int		retx;
	int		rety;

	retx = lst[0];
	rety = lst[1];
	nexty = lst[1] + lst[2];
	nextx = lst[0] + lst[2];
	while (lst[1] < nexty)
	{
		lst[0] = retx;
		while (lst[0] < nextx)
		{
			if (lst[0] >= 0 && lst[0] < info->width
				&& lst[1] >= 0 && lst[1] < info->height)
				putpixel(img, lst[0], lst[1], color);
			lst[0] += 1;
		}
		lst[1] += 1;
	}
	lst[0] = retx;
	lst[1] = rety;
}

void	putmaptoimg2(t_info *info, int lst[2], char c, int diff)
{
	int	lst_diff[3];

	lst_diff[0] = lst[0];
	lst_diff[1] = lst[1];
	lst_diff[2] = diff;
	if (c == '2')
		putsquare(info, &info->img[info->current_img], lst_diff, 0x00FFFF);
	if (c == '1')
		putsquare(info, &info->img[info->current_img], lst_diff, 0xFFFFFF);
	if (c == '0' || c == 'X')
		putsquare(info, &info->img[info->current_img], lst_diff, 0x0000FF);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		putsquare(info, &info->img[info->current_img], lst_diff, 0x00FF00);
}

void	putmaptoimg(t_info *info, t_img *img)
{
	int	xmap;
	int	ymap;
	int	lst[2];
	int	diff;
	int	coords[2];

	diff = getdiff(info);
	ymap = 0;
	lst[1] = 0;
	while (info->map[ymap])
	{
		xmap = 0;
		lst[0] = 0;
		while (info->map[ymap][xmap])
		{
			putmaptoimg2(info, lst, info->map[ymap][xmap], diff);
			lst[0] += diff;
			xmap++;
		}
		lst[1] += diff;
		ymap++;
	}
	coords[0] = diff * info->player.x;
	coords[1] = diff * info->player.y;
	putplayer(info, img, coords, 0xFF0000);
}

void	putminimap(t_info *info, t_img *img)
{
	int	x;
	int	y;
	int	lst[2];

	lst[1] = 0;
	y = (int)info->player.y - 2;
	while (y < (int)info->player.y + 3)
	{
		lst[0] = 0;
		x = (int)info->player.x - 2;
		while (x < (int)info->player.x + 3)
		{
			if (x >= 0 && y >= 0 && x < info->xmax && y < info->ymax)
				putmaptoimg2(info, lst, info->map[y][x], 25);
			lst[0] += 25;
			x++;
		}
		lst[1] += 25;
		y++;
	}
	lst[0] = 50 + (25 * (info->player.x - floor(info->player.x)));
	lst[1] = 50 + (25 * (info->player.y - floor(info->player.y)));
	putplayer(info, img, lst, 0xFF0000);
}
