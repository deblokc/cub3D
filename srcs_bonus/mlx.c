/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:39:50 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/08 18:28:44 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	getdiff(t_info *info)
{
	int	x;
	int	y;
	int	max;

	y = 0;
	x = 0;
	max = WIDTH;
	if (max > HEIGHT)
		max = HEIGHT;
	while (info->map[y])
		y++;
	while (info->map[0][x])
		x++;
	if (max/(x + 10) > max/(y + 10))
		return (max/(y + 10));
	return (max/(x + 10));
}

void	putplayer(t_img *img, int x, int y, t_info *info, unsigned int color)
{
	int	diff;
	int	nexty;
	int	nextx;
	int	rety;
	int	retx;
	char *dest;

	diff = getdiff(info);
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
			{
				dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
				*(unsigned int*)dest = color; 
			}
			x++;
		}
		y++;
	}
}

void	putsquare(t_img *img, int x, int y, t_info *info, unsigned int color)
{
	int	diff;
	int	nexty;
	int	nextx;
	int	retx;
	int	rety;
	char *dest;

	diff = getdiff(info);
	retx = x;
	rety = y;
	nexty = y + diff;
	nextx = x + diff;
	while (y < nexty)
	{
		x = retx;
		while (x < nextx)
		{
			if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
			{
				dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
				*(unsigned int*)dest = color; 
			}
			x++;
		}
		y++;
	}
}

void	putmaptoimg(t_info *info, t_img *img)
{
	int	xmap;
	int	ymap;
	int	ximg;
	int	yimg;
	int	diff;

	diff = getdiff(info);
	ymap = 0;
	ximg = 0;
	yimg = 0;
	while (info->map[ymap])
	{
		xmap = 0;
		ximg = 0;
		while (info->map[ymap][xmap])
		{
			if (info->map[ymap][xmap] == '1')
				putsquare(img, ximg, yimg, info, 0x00FFFFFF);
			if (info->map[ymap][xmap] == '0')
				putsquare(img, ximg, yimg, info, 0x990000FF);
			if (info->map[ymap][xmap] == 'N' || info->map[ymap][xmap] == 'W' || info->map[ymap][xmap] == 'E' || info->map[ymap][xmap] == 'S')
				putsquare(img, ximg, yimg, info, 0x0000FF00);
			ximg += diff;
			xmap++;
		}
		yimg += diff;
		ymap++;
	}
	putplayer(img, diff * info->player.x, diff * info->player.y, info, 0xFF0000);
}

int	hook(int keycode, t_info *info)
{
	if (keycode == 65307)
		closewin(info);
	if (keycode == 119)
		info->movement += 1;
	if (keycode == 115)
		info->movement += (1 << 1);
	if (keycode == 97)
		info->movement += (1 << 2);
	if (keycode == 100)
		info->movement += (1 << 3);
	if (keycode == 65363)
		info->movement += (1 << 4);
	if (keycode == 65361)
		info->movement += (1 << 5);
	if (keycode == 65289)
		info->tabmap = 1;
	loop(info);
	return (0);
}

int	hook_release(int keycode, t_info *info)
{
	if (keycode == 119)
		info->movement -= 1;
	if (keycode == 115)
		info->movement -= (1 << 1);
	if (keycode == 97)
		info->movement -= (1 << 2);
	if (keycode == 100)
		info->movement -= (1 << 3);
	if (keycode == 65363)
		info->movement -= (1 << 4);
	if (keycode == 65361)
		info->movement -= (1 << 5);
	if (keycode == 65289)
		info->tabmap = 0;
	loop(info);
	return (0);
}

int	gettext(t_texture *text, t_info *info)
{
	text->texture.img = mlx_xpm_file_to_image(info->mlx, text->path, \
			&text->width, &text->height);
	if (!text->texture.img)
		return (puterr("Impossible d'ouvrir ", info), \
				ft_putstr_fd(text->path, 2), ft_putstr_fd(" !\n", 2), 1);
	text->texture.addr = mlx_get_data_addr(text->texture.img, \
			&text->texture.bits_per_pixel, &text->texture.line_length,
			&text->texture.endian);
	return (0);
}

int	gettexture(t_info *info)
{
	if (gettext(&info->no, info) || gettext(&info->so, info) \
			|| gettext(&info->we, info) || gettext(&info->ea, info))
		return (1);
	return (0);
}

int	loop(t_info *info)
{
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
	info->current_img += 1;
	if (info->current_img >= NB_IMG)
		info->current_img = 0;
	raisewalls(info);
	if (info->tabmap)
		putmaptoimg(info, &info->img[info->current_img]);
	mlx_put_image_to_window(info->mlx, info->win, \
			info->img[info->current_img].img, 0, 0);
	return (0);
}

int	mlx(t_info *info)
{
	int	i;

	info->movement = 0;
	info->mlx = mlx_init();
	if (gettexture(info))
		return (1);
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "cub3D");
	i = 0;
	while (i < NB_IMG)
	{
		info->img[i].img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
		info->img[i].addr = mlx_get_data_addr(info->img[i].img, \
				&info->img[i].bits_per_pixel, &info->img[i].line_length, \
				&info->img[i].endian);
		i++;
	}
	info->current_img = i;
	loop(info);
	mlx_do_key_autorepeatoff(info->mlx);
	mlx_hook(info->win, 17, 0, closewin, info);
	mlx_hook(info->win, 2, 1L << 0, hook, info);
	mlx_hook(info->win, 3, 1L << 1, hook_release, info);
	mlx_loop_hook(info->mlx, loop, info);
	mlx_loop(info->mlx);
	return (0);
}
