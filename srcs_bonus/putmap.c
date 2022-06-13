/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:02:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/13 19:02:43 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	putplayer(t_img *img, int x, int y, unsigned int color)
{
	int	nexty;
	int	nextx;
	int	rety;
	int	retx;

	retx = x - 3;
	rety = y;
	nexty = y + 3;
	nextx = x + 3;
	y -= 3;
	while (y < nexty)
	{
		x = retx;
		while (x < nextx)
		{
			if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
				putpixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	putsquare(t_img *img, int lst[2], unsigned int color, int diff)
{
	int		nexty;
	int		nextx;
	int		retx;
	int		rety;

	retx = lst[0];
	rety = lst[1];
	nexty = lst[1] + diff;
	nextx = lst[0] + diff;
	while (lst[1] < nexty)
	{
		lst[0] = retx;
		while (lst[0] < nextx)
		{
			if (lst[0] >= 0 && lst[0] < WIDTH && lst[1] >= 0 && lst[1] < HEIGHT)
				putpixel(img, lst[0], lst[1], color);
			lst[0]++;
		}
		lst[1]++;
	}
	lst[0] = retx;
	lst[1] = rety;
}

void	putmaptoimg2(t_info *info, int lst[2], char c, int diff)
{
	if (c == '2')
		putsquare(&info->img[info->current_img], lst, 0x00FFFF, diff);
	if (c == '1')
		putsquare(&info->img[info->current_img], lst, 0xFFFFFF, diff);
	if (c == '0' || c == 'X')
		putsquare(&info->img[info->current_img], lst, 0x0000FF, diff);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		putsquare(&info->img[info->current_img], lst, 0x00FF00, diff);
}

void	putmaptoimg(t_info *info, t_img *img)
{
	int	xmap;
	int	ymap;
	int	lst[2];
	int	diff;

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
	putplayer(img, diff * info->player.x, diff * info->player.y, 0xFF0000);
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
	putplayer(img, 50 + (25 * (info->player.x - floor(info->player.x))), \
			50 + (25 * (info->player.y - floor(info->player.y))), 0xFF0000);
}
