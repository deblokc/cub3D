/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:39:50 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/01 20:35:03 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	closewin(t_info *info)
{
	freeinfo(info);
	exit(0);
}

int	hook(int keycode, t_info *info)
{
	printf("%d\n", keycode);
	if (keycode == 65307)
		closewin(info);
	return (0);
}

int	gettext(t_texture *text, t_info *info)
{
	text->texture = mlx_xpm_file_to_image(info->mlx, text->path, &text->width, &text->height);
	if (!text->texture)
		return (puterr("Impossible d'ouvrir ", info), ft_putstr_fd(text->path, 2), ft_putstr_fd(" !\n", 2), 1);
	return (0);
}

int	gettexture(t_info *info)
{
	if (gettext(&info->no, info) || gettext(&info->so, info) \
			|| gettext(&info->we, info) || gettext(&info->ea, info))
		return (1);
	return (0);
}

int	mlx(t_info *info)
{
	int decalage;
	double	factor;

	factor = 20;

	decalage = 0;
	info->mlx = mlx_init();
	if (gettexture(info))
		return (1);
	info->win = mlx_new_window(info->mlx, WIDTH, HEIGHT, "cub3D");
	printf("%x\n", info->f);
	printf("%x\n", info->c);
	t_img tmp;

	tmp.img = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length, &tmp.endian);
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
	}
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
	mlx_put_image_to_window(info->mlx, info->win, tmp.img, decalage, 0);
	mlx_hook(info->win, 17, 0, closewin, info);
	mlx_hook(info->win, 2, 1L << 0, hook, info);
	mlx_loop(info->mlx);
	return (0);
}
