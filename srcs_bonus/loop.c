/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:05:08 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/14 15:53:57 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	loop1(t_info *info)
{
	handle_doors(info);
	if (info->movement & 1 && !(info->movement & (1 << 1)))
		goforward(info);
	if (info->movement & (1 << 1) && !(info->movement & 1))
		goback(info);
	if (info->movement & (1 << 2) && !(info->movement & (1 << 3)))
		goleft(info);
	if (info->movement & (1 << 3) && !(info->movement & (1 << 2)))
		goright(info);
	if (info->movement & (1 << 4) && !(info->movement & (1 << 5)))
		turnright(info);
	if (info->movement & (1 << 5) && !(info->movement & (1 << 4)))
		turnleft(info);
	if (info->no.numtext == info->no.numtextmax - 1)
		info->no.numtext = 0;
	else
		info->no.numtext++;
	if (info->so.numtext == info->so.numtextmax - 1)
		info->so.numtext = 0;
	else
		info->so.numtext++;
}

void	loop2(t_info *info)
{
	if (info->we.numtext == info->we.numtextmax - 1)
		info->we.numtext = 0;
	else
		info->we.numtext++;
	if (info->ea.numtext == info->ea.numtextmax - 1)
		info->ea.numtext = 0;
	else
		info->ea.numtext++;
	if (info->door.numtext == info->door.numtextmax - 1)
		info->door.numtext = 0;
	else
		info->door.numtext++;
	if (info->exit.numtext == info->exit.numtextmax - 1)
		info->exit.numtext = 0;
	else
		info->exit.numtext++;
	raisewalls(info);
	if (info->tabmap)
		putmaptoimg(info, &info->img[info->current_img]);
	else
		putminimap(info, &info->img[info->current_img]);
}

void	putend(t_info *info)
{
	int				x;
	int				y;
	double			ystep;
	double			xstep;
	char			*dest;

	ystep = ((double)info->end.texture[info->end.numtext].height \
			/ (double)(info->height + 1));
	xstep = ((double)info->end.texture[info->end.numtext].width \
			/ (double)(info->width + 1));
	y = 0;
	while (y < info->height)
	{
		dest = info->end.texture[info->end.numtext].addr \
		+ (int)(ystep * y) *info->end.texture[info->end.numtext].line_length;
		x = -1;
		while (++x < info->width)
			putpixel(&info->img[info->current_img], x, y, \
				(*(unsigned int *)(dest + (int)(xstep * x) \
				*(info->end.texture[info->end.numtext].bits_per_pixel / 8))));
		y++;
	}
}

int	loop(t_info *info)
{
	info->current_img += 1;
	if (info->current_img >= NB_IMG)
		info->current_img = 0;
	if (!info->asended)
	{
		loop1(info);
		loop2(info);
		if (info->click && info->xmouse != info->newxmouse)
		{
			info->player.angle -= ((double)(info->xmouse - info->newxmouse) \
					/ (double)info->width) * (M_PI / 2);
			info->xmouse = info->newxmouse;
		}
		if (info->map[(int)info->player.y][(int)info->player.x] == 'X')
			info->asended = 1;
	}
	else
		putend(info);
	mlx_do_sync(info->mlx);
	mlx_put_image_to_window(info->mlx, info->win, \
			info->img[info->current_img].img, 0, 0);
	return (0);
}

void	hook_list(t_info *info)
{
	info->asended = 0;
	loop(info);
	mlx_do_key_autorepeatoff(info->mlx);
	mlx_hook(info->win, 17, 0, closewin, info);
	mlx_hook(info->win, 2, 1L << 0, hook, info);
	mlx_hook(info->win, 3, 1L << 1, hook_release, info);
	mlx_hook(info->win, 4, 1L << 2, mouse_press, info);
	mlx_hook(info->win, 5, 1L << 3, mouse_release, info);
	mlx_hook(info->win, 6, 1L << 6, mouse_move, info);
	mlx_loop_hook(info->mlx, loop, info);
	mlx_loop(info->mlx);
}
