/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:16:16 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/06 16:17:36 by tnaton           ###   ########.fr       */
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

void	freetexture(t_info *info)
{
	if (info->no.texture.img)
		mlx_destroy_image(info->mlx, info->no.texture.img);
	if (info->so.texture.img)
		mlx_destroy_image(info->mlx, info->so.texture.img);
	if (info->we.texture.img)
		mlx_destroy_image(info->mlx, info->we.texture.img);
	if (info->ea.texture.img)
		mlx_destroy_image(info->mlx, info->ea.texture.img);
}

void	freeinfo(t_info *info)
{
	free(info->no.path);
	free(info->so.path);
	free(info->we.path);
	free(info->ea.path);
	freeallchunk(info->lstmap);
	freecharchar(info->map);
	freetexture(info);
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
