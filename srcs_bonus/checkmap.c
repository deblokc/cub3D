/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:18:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/13 18:54:08 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	checkcub(char **map, int i, int j)
{
	if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
		return (0);
	if (!ischr(map[i - 1][j - 1]) || !ischr(map[i - 1][j]) \
			|| !ischr(map[i - 1][j + 1]))
		return (0);
	if (!ischr(map[i][j - 1]) || !ischr(map[i][j + 1]))
		return (0);
	if (!ischr(map[i + 1][j - 1]) || !ischr(map[i + 1][j]) \
			|| !ischr(map[i + 1][j + 1]))
		return (0);
	return (1);
}

void	infodir(t_info *info, char c, int i, int j)
{
	info->dir = c;
	if (c == 'N')
		info->player.angle = M_PI / 2;
	if (c == 'W')
		info->player.angle = M_PI;
	if (c == 'S')
		info->player.angle = (3 * M_PI) / 2;
	if (c == 'E')
		info->player.angle = 2 * M_PI;
	info->player.x = j + 0.5;
	info->player.y = i + 0.5;
}

int	checkdoor(char **map, int i, int j)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (map[i][x])
		x++;
	while (map[y])
		y++;
	if (i == 0 || j == 0 || i >= y - 1 || j >= x - 1)
		return (0);
	if (map[i][j - 1] == '1' && map[i][j + 1] == '1' \
			&& isfloor(map[i + 1][j]) && isfloor(map[i - 1][j]))
		return (1);
	if (map[i - 1][j] == '1' && map[i + 1][j] == '1' \
			&& isfloor(map[i][j + 1]) && isfloor(map[i][j - 1]))
		return (1);
	return (0);
}

void	checkcharmap(char **map, int i, int j, t_info *info)
{
	if (!ischr(map[i][j]) && map[i][j] != ' ')
	{
		printerrcoo("Charactere invalide dans la map en ", i, j, info);
		info->isvalid = 0;
	}
	if (map[i][j] == '0' || map[i][j] == 'E' || map[i][j] == 'W' \
			|| map[i][j] == 'N' || map[i][j] == 'S' \
			|| map[i][j] == '2' || map[i][j] == 'X')
	{
		if (!checkcub(map, i, j))
		{
			printerrcoo("Il manque des murs pour le chemin en ", \
					i, j, info);
			info->isvalid = 0;
		}
		if (map[i][j] == '2')
		{
			if (!checkdoor(map, i, j))
			{
				printerrcoo("Porte invalide en ", i, j, info);
				info->isvalid = 0;
			}
			add_door(info, i, j);
		}
	}
}

int	isvalid(char **map, t_info *info)
{
	int	i;
	int	j;

	info->isvalid = 1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			checkcharmap(map, i, j, info);
			dirmap(map, i, j, info);
			j++;
		}
		i++;
	}
	info->xmax = j;
	info->ymax = i;
	if (info->dir && info->isvalid)
		return (1);
	else if (!info->dir)
		return (puterr("Pas de point de spawn !\n", info), 0);
	return (0);
}
