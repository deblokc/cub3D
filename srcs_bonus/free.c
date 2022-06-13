/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:16:16 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/13 16:09:14 by tnaton           ###   ########.fr       */
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

void	freetexture(t_info *info)
{
	freetext(info->no, info->mlx);
	freetext(info->so, info->mlx);
	freetext(info->we, info->mlx);
	freetext(info->ea, info->mlx);
	freetext(info->door, info->mlx);
	freetext(info->exit, info->mlx);
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
