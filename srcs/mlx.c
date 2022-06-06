/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:39:50 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/06 12:28:02 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	turnleft(t_info *info)
{
	info->player.angle += ((5 * M_PI) / 180);
	if (info->player.angle == 0)
		info->player.angle = 2 * M_PI;
	loop(info);
}

int	hook(int keycode, t_info *info)
{
	if (keycode == 65307)
		closewin(info);
	if (keycode == 119)
		goforward(info);
	if (keycode == 115)
		goback(info);
	if (keycode == 97)
		goleft(info);
	if (keycode == 100)
		goright(info);
	if (keycode == 65363)
		turnright(info);
	if (keycode == 65361)
		turnleft(info);
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

void	loop(t_info *info)
{
	info->current_img += 1;
	if (info->current_img >= NB_IMG)
		info->current_img = 0;
	raisewalls(info);
	mlx_put_image_to_window(info->mlx, info->win, \
			info->img[info->current_img].img, 0, 0);
}

int	mlx(t_info *info)
{
	int	i;

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
	mlx_hook(info->win, 17, 0, closewin, info);
	mlx_hook(info->win, 2, 1L << 0, hook, info);
	mlx_loop(info->mlx);
	return (0);
}
