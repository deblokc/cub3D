/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:39:50 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/14 22:04:25 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	getdiff(t_info *info)
{
	int	max;

	max = info->width;
	if (max > info->height)
		max = info->height;
	if (max / (info->xmax) > max / (info->ymax))
		return (max / (info->ymax));
	return (max / (info->xmax));
}

void	putpixel(t_img *img, int x, int y, unsigned int color)
{
	char	*dest;

	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

int	gettexture(t_info *info)
{
	if (!info->door.path)
		info->door.path = ft_strdup(DOOR_PATH);
	if (!info->exit.path)
		info->exit.path = ft_strdup(EXIT_PATH);
	if (!info->end.path)
		info->end.path = ft_strdup(END_PATH);
	if (gettext(&info->no, info) || gettext(&info->so, info) \
			|| gettext(&info->we, info) || gettext(&info->ea, info) \
			|| gettext(&info->door, info) || gettext(&info->exit, info) \
			|| gettext(&info->end, info))
		return (1);
	return (0);
}

int	mlx(t_info *info)
{
	int	i;

	info->movement = 0;
	info->tabmap = 0;
	info->click = 0;
	info->mlx = mlx_init();
	if (gettexture(info))
		return (1);
	mlx_get_screen_size(info->mlx, &info->width, &info->height);
	info->width -= 100;
	info->height -= 100;
	info->win = mlx_new_window(info->mlx, info->width, info->height, "cub3D");
	i = 0;
	while (i < NB_IMG)
	{
		info->img[i].img = mlx_new_image(info->mlx, info->width, info->height);
		info->img[i].addr = mlx_get_data_addr(info->img[i].img, \
				&info->img[i].bits_per_pixel, &info->img[i].line_length, \
				&info->img[i].endian);
		i++;
	}
	info->current_img = i;
	hook_list(info);
	return (0);
}
