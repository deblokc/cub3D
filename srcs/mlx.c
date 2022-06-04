/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:39:50 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/04 12:56:55 by tnaton           ###   ########.fr       */
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
	freeinfo(info);
	exit(0);
}

int	iswall(t_info *info, double y, double x)
{
	if (info->map[(int)floor(y)][(int)floor(x)] == '1')
		return (1);
	return (0);
}

void	goforward(t_info *info)
{
	double	oldy;
	double	oldx;

	oldy = info->player.y;
	oldx = info->player.x;
//	mlx_destroy_image(info->mlx, info->img.img);
	if (sin(info->player.angle) > 0)
	{
		if (!iswall(info, (info->player.y - (sin(info->player.angle) * (STEP)) - 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle) * STEP);
		else
			info->player.y = floor(info->player.y) + 0.1;
	}
	else
	{
		if (!iswall(info, (info->player.y - (sin(info->player.angle) * (STEP)) + 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle) * STEP);
		else
			info->player.y = ceil(info->player.y) - 0.1;
	}
	if (cos(info->player.angle) > 0)
	{
		if (!iswall(info, oldy, (info->player.x + cos(info->player.angle) * (STEP) + 0.1)))
			info->player.x += (cos(info->player.angle) * STEP);
		else
			info->player.x = ceil(info->player.x) - 0.1;
	}
	else
	{
		if (!iswall(info, oldy, (info->player.x + cos(info->player.angle) * (STEP) - 0.1)))
			info->player.x += (cos(info->player.angle) * STEP);
		else
			info->player.x = floor(info->player.x) + 0.1;
	}
	if (iswall(info, info->player.y, info->player.x))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
//	printf("Player position on vector: %.4f ; %.4f\n", info->player.x, info->player.y);
	loop(info);
}

void	goback(t_info *info)
{
	double	oldy;
	double	oldx;

	oldy = info->player.y;
	oldx = info->player.x;
//	mlx_destroy_image(info->mlx, info->img.img);
	if (sin(info->player.angle) < 0)
	{
		if (!iswall(info, (info->player.y + (sin(info->player.angle) * (STEP)) - 0.1), info->player.x))
			info->player.y += (sin(info->player.angle) * STEP);
		else
			info->player.y = floor(info->player.y) + 0.1;
	}
	else
	{
		if (!iswall(info, (info->player.y + (sin(info->player.angle) * (STEP)) + 0.1), info->player.x))
			info->player.y += (sin(info->player.angle) * STEP);
		else
			info->player.y = ceil(info->player.y) - 0.1;
	}
	if (cos(info->player.angle) < 0)
	{
		if (!iswall(info, oldy, (info->player.x - cos(info->player.angle) * (STEP) + 0.1)))
			info->player.x -= (cos(info->player.angle) * STEP);
		else
			info->player.x = ceil(info->player.x) - 0.1;
	}
	else
	{
		if (!iswall(info, oldy, (info->player.x - cos(info->player.angle) * (STEP) - 0.1)))
			info->player.x -= (cos(info->player.angle) * STEP);
		else
			info->player.x = floor(info->player.x) + 0.1;
	}
	if (iswall(info, info->player.y, info->player.x))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
//	printf("Player position on vector: %.4f ; %.4f\n", info->player.x, info->player.y);
	loop(info);
}

void	turnright(t_info *info)
{
//	mlx_destroy_image(info->mlx, info->img.img);
	info->player.angle -= ((5 * M_PI)/180);
	if (info->player.angle == 0)
		info->player.angle = 2 * M_PI;
//	printf("%.4f\n", info->player.angle);
	loop(info);
}

void	turnleft(t_info *info)
{
//	mlx_destroy_image(info->mlx, info->img.img);
	info->player.angle += ((5 * M_PI)/180);
	if (info->player.angle == 0)
		info->player.angle = 2 * M_PI;
//	printf("%.4f\n", info->player.angle);
	loop(info);
}

int	hook(int keycode, t_info *info)
{
//	printf("%d\n", keycode);
	if (keycode == 65307)
		closewin(info);
	if (keycode == 119)
		goforward(info);
	if (keycode == 115)
		goback(info);
	if (keycode == 65363)
		turnright(info);
	if (keycode == 65361)
		turnleft(info);
	return (0);
}

int	gettext(t_texture *text, t_info *info)
{
	text->texture.img = mlx_xpm_file_to_image(info->mlx, text->path, &text->width, &text->height);
	if (!text->texture.img)
		return (puterr("Impossible d'ouvrir ", info), ft_putstr_fd(text->path, 2), ft_putstr_fd(" !\n", 2), 1);
	text->texture.addr = mlx_get_data_addr(text->texture.img, &text->texture.bits_per_pixel, &text->texture.line_length,
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

	diff = getdiff(info) + 1;
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
	y = (info->player.y + (-sin(info->player.angle) * STEP)) * diff;
	x = (info->player.x + (cos(info->player.angle) * STEP)) * diff;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dest = color; 
	}
	y = (info->player.y + (sin(info->player.angle) * STEP)) * diff;
	x = (info->player.x + (-cos(info->player.angle) * STEP)) * diff;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dest = color; 
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

	diff = getdiff(info) + 1;
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
				putsquare(img, ximg, yimg, info, 0xFFFFFF);
			if (info->map[ymap][xmap] == '0')
				putsquare(img, ximg, yimg, info, 0x0000FF);
			if (info->map[ymap][xmap] == 'N' || info->map[ymap][xmap] == 'W' || info->map[ymap][xmap] == 'E' || info->map[ymap][xmap] == 'S')
				putsquare(img, ximg, yimg, info, 0x00FF00);
			ximg += diff;
			xmap++;
		}
		yimg += diff;
		ymap++;
	}
	putplayer(img, diff * info->player.x, diff * info->player.y, info, 0xFF0000);
}

void	loop(t_info *info)
{
	//	putmaptoimg(info, &info->img);*/
	info->current_img += 1;
	if (info->current_img >= NB_IMG)
		info->current_img = 0;
	raisewalls(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img[info->current_img].img, 0, 0);
}

int	mlx(t_info *info)
{
	int i;

	info->mlx = mlx_init();
	if (gettexture(info))
		return (1);
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "cub3D");
	i = 0;
	while (i < NB_IMG)
	{
		info->img[i].img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
		info->img[i].addr = mlx_get_data_addr(info->img[i].img, &info->img[i].bits_per_pixel, &info->img[i].line_length, &info->img[i].endian);
		i++;
	}
	info->current_img = i;
	loop(info);
	mlx_hook(info->win, 17, 0, closewin, info);
	mlx_hook(info->win, 2, 1L << 0, hook, info);
	mlx_loop(info->mlx);
	return (0);
}

/*
	int i = 0;
	int j = 0;
	char *dest;
	while (j < HEIGHT / 2)
	{
		i = 0;
		while (i < WIDTH)
		{
			dest = tmp.addr + (j * tmp.line_length + i * (tmp.bits_per_pixel / 8));
			*(unsigned int*)dest = info->c; 
			i++;
		}
		j++;
	}
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			dest = tmp.addr + (j * tmp.line_length + i * (tmp.bits_per_pixel / 8));
			*(unsigned int*)dest = info->f; 
			i++;
		}
		j++;
	}*/
/*	tmp.img = info->no.texture;
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length, &tmp.endian);
	printf("%d\n", tmp.line_length);
	printf("%d\n", tmp.endian);
	printf("%s\n", tmp.addr);
	mlx_put_image_to_window(info->mlx, info->win, info->no.texture, decalage, 0);
	t_img	img;
	img.img = mlx_new_image(info->mlx, (int)ceil((double)info->no.width * factor), (int)ceil((double)info->no.height * factor));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	int	i;
	int j = 0;
	char	*dst;
	char	*dst2;
	while (j < ((double)info->no.height * factor))
	{
		i = 0;
		while (i < ((double)info->no.width * factor))
		{
			dst = tmp.addr + ((int)round((double)(j * (double)((double)info->no.height / ((double)info->no.height * factor)))) * tmp.line_length + (int)round((double)((double)i * (double)((double)info->no.width / (double)(info->no.width * factor)))) * (tmp.bits_per_pixel / 8));
			dst2 = img.addr + (j * img.line_length + i * (img.bits_per_pixel / 8));
	
			*(unsigned int*)dst2 = *(unsigned int*)dst;
			i++;
		}
		j++;
	}
	decalage += info->no.width;
	mlx_put_image_to_window(info->mlx, info->win, img.img, decalage, 0);
	mlx_put_image_to_window(info->mlx, info->win, info->so.texture, decalage, 0);
	decalage += info->so.width;
	mlx_put_image_to_window(info->mlx, info->win, info->we.texture, decalage, 0);
	decalage += info->we.width;
	mlx_put_image_to_window(info->mlx, info->win, info->ea.texture, decalage, 0);
	decalage += info->ea.width;
*/	

