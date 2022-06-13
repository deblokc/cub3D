/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:51:09 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/13 18:53:54 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	dirmap(char **map, int i, int j, t_info *info)
{
	if (map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N' \
			|| map[i][j] == 'S')
	{
		if (!info->dir)
			infodir(info, map[i][j], i, j);
		else
		{
			printerrcoo("Point de spawn excedant en ", i, j, info);
			info->isvalid = 0;
		}
	}
}

int	isfloor(char c)
{
	return (c == '0' || c == 'X' || c == 'E' \
			|| c == 'W' || c == 'N' || c == 'S');
}
