/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:16:16 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/13 18:51:32 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	freeallchunk(t_map *map)
{
	t_map	*tmp;

	while (map)
	{
		tmp = map;
		map = map->next;
		free(tmp);
	}
}

void	freecharchar(char **lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst[i])
			free(lst[i++]);
		free(lst);
	}
}

void	freetext(t_texture text, void *mlx)
{
	int	i;

	i = 0;
	if (text.texture)
	{
		while (i < text.numtextmax)
		{
			mlx_destroy_image(mlx, text.texture[i].img);
			i++;
		}
	}
	free(text.texture);
}

void	freeinfo(t_info *info)
{
	free(info->no.path);
	free(info->so.path);
	free(info->we.path);
	free(info->ea.path);
	if (info->door.path)
		free(info->door.path);
	if (info->exit.path)
		free(info->exit.path);
	freeallchunk(info->lstmap);
	freecharchar(info->map);
	freetexture(info);
	freedoors(info);
	if (info->win)
		mlx_destroy_window(info->mlx, info->win);
	if (info->mlx)
	{
		mlx_destroy_display(info->mlx);
		free(info->mlx);
	}
}

void	freelstmap(t_map *map)
{
	while (map)
	{
		free(map->ligne);
		map = map->next;
	}
}
