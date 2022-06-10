/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:16:16 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/09 17:57:24 by tnaton           ###   ########.fr       */
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
	int	i;

	i = 0;
	if (info->no.texture)
	{
		while (i < info->no.numtextmax)
		{
			mlx_destroy_image(info->mlx, info->no.texture[i].img);
			i++;
		}
	}
	free(info->no.texture);
	i = 0;
	if (info->so.texture)
	{
		while (i < info->so.numtextmax)
		{
			mlx_destroy_image(info->mlx, info->so.texture[i].img);
			i++;
		}
	}
	free(info->so.texture);
	i = 0;
	if (info->we.texture)
	{
		while (i < info->we.numtextmax)
		{
			mlx_destroy_image(info->mlx, info->we.texture[i].img);
			i++;
		}
	}
	free(info->we.texture);
	i = 0;
	if (info->ea.texture)
	{
		while (i < info->ea.numtextmax)
		{
			mlx_destroy_image(info->mlx, info->ea.texture[i].img);
			i++;
		}
	}
	free(info->ea.texture);
}

void	freedoors(t_info *info)
{
	t_door	*current;
	t_door	*next;

	current = info->doors;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
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
