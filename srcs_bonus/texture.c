/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:07:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/14 12:08:28 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	gettextnodir(t_texture *text, t_info *info)
{
	text->numtextmax = 1;
	text->texture = malloc(sizeof(t_img) * 2);
	text->texture[0].img = mlx_xpm_file_to_image(info->mlx, text->path, \
			&text->texture[0].width, &text->texture[0].height);
	if (!text->texture[0].img)
	{
		free(text->texture);
		text->texture = NULL;
		return (puterr("Impossible d'ouvrir ", info), \
				ft_putstr_fd(text->path, 2), ft_putstr_fd(" !\n", 2), 1);
	}
	text->texture[0].addr = mlx_get_data_addr(text->texture[0].img, \
			&text->texture[0].bits_per_pixel, &text->texture[0].line_length,
			&text->texture[0].endian);
	return (0);
}

int	gettextdirerr(t_texture *text, t_info *info, DIR *dir, int i)
{
	closedir(dir);
	i++;
	while (i < text->numtextmax)
	{
		mlx_destroy_image(info->mlx, text->texture[i].img);
		i++;
	}
	free(text->texture);
	text->texture = NULL;
	return (puterr("Impossible d'ouvrir ", info), \
		ft_putstr_fd(text->path, 2), ft_putstr_fd(" !\n", 2), 1);
}

void	initgettextdir(t_texture *text, DIR *dir, int *i)
{
	struct dirent	*file;

	*i = 0;
	file = readdir(dir);
	while (file != NULL)
	{
		*(i) += 1;
		file = readdir(dir);
	}
	*(i) -= 2;
	text->texture = malloc(sizeof(t_img) * (*(i) + 1));
	text->numtextmax = *(i);
}

int	gettextdir(t_texture *text, t_info *info, DIR *dir)
{
	char			*tmp;
	int				i;

	initgettextdir(text, dir, &i);
	while (i--)
	{
		tmp = ft_strjoin_free(ft_strdup(text->path), ft_itoa(i));
		text->texture[i].img = mlx_xpm_file_to_image(info->mlx, tmp, \
				&text->texture[i].width, &text->texture[i].height);
		if (!text->texture[i].img)
			return (free(tmp), gettextdirerr(text, info, dir, i));
		text->texture[i].addr = mlx_get_data_addr(text->texture[i].img, \
			&text->texture[i].bits_per_pixel, &text->texture[i].line_length, \
			&text->texture[i].endian);
		free(tmp);
	}
	return (0);
}

int	gettext(t_texture *text, t_info *info)
{
	DIR	*dir;

	dir = opendir(text->path);
	text->numtext = 0;
	if (!dir)
	{
		if (gettextnodir(text, info))
			return (1);
	}
	else
	{
		if (gettextdir(text, info, dir))
			return (1);
	}
	closedir(dir);
	return (0);
}
