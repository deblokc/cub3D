/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:09:08 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/03 18:07:09 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_map	*newchunk(char *str)
{
	t_map	*tmp;

	tmp = malloc(sizeof(t_map));
	if (!tmp)
		return (NULL);
	tmp->next = NULL;
	tmp->ligne = str;
	return (tmp);
}

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

int	ispointcub(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i < 5)
		return (0);
	if (str[i - 1] == 'b' && str[i - 2] == 'u' && str[i - 3] == 'c' \
			&& str[i - 4] == '.' && str[i - 5] != '/')
		return (1);
	return (0);
}

int	ischr(char c)
{
	return (c == '0' || c == '1' || c == 'E' \
			|| c == 'W' || c == 'N' || c == 'S');
}

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

void	printerrcoo(char *str, int i, int j, t_info *info)
{
	char	*tmp;

	puterr(str, info);
	tmp = ft_itoa(i);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd(", ", 2);
	free(tmp);
	tmp = ft_itoa(j);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd(" !\n", 2);
}

int	isvalid(char **map, t_info *info)
{
	int	i;
	int	j;
	int	isvalid;

	isvalid = 1;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ischr(map[i][j]) && map[i][j] != ' ')
			{
				printerrcoo("Charactere invalide dans la map en ", i, j, info);
				isvalid = 0;
			}
			if (map[i][j] == '0' || map[i][j] == 'E' || map[i][j] == 'W' \
					|| map[i][j] == 'N' || map[i][j] == 'S')
				if (!checkcub(map, i, j))
				{
					printerrcoo("Il manque des murs pour le chemin en ", i, j, info);
					isvalid = 0;
				}
			if (map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N' \
					|| map[i][j] == 'S')
			{
				if (!info->dir)
				{
					info->dir = map[i][j];
					if (map[i][j] == 'N')
						info->player.angle = M_PI/2;
					if (map[i][j] == 'W')
						info->player.angle = M_PI;
					if (map[i][j] == 'S')
						info->player.angle = (3 * M_PI) / 2;
					if (map[i][j] == 'E')
						info->player.angle = 2 * M_PI;
					info->player.x = j + 0.5;
					info->player.y = i + 0.5;
				}
				else
				{
					printerrcoo("Point de spawn excedant en ", i, j, info);
					isvalid = 0;
				}
			}
			j++;
		}
		i++;
	}
	if (info->dir && isvalid)
		return (1);
	else if (!info->dir)
		return (puterr("Pas de point de spawn !\n", info), 0);
	return (0);
}

void	freelstmap(t_map *map)
{
	while (map)
	{
		free(map->ligne);
		map = map->next;
	}
}

int	main(int ac, char **av)
{
	t_map	*map;
	t_map	*current;
	t_info	info;
	int		fd;

	if (ac != 2)
		return (ft_putstr_fd("Error\nNombre d'arg invalide !\n", 2), 1);
	if (!ispointcub(av[1]))
		return (ft_putstr_fd("Error\nExtension invalide !\n", 2), 1);
	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
		return (ft_putstr_fd("Error\nFichier d'entree inaccessible !\n", 2), 1);
	current = newchunk(get_next_line(fd));
	if (!current->ligne)
		return (free(current), \
				ft_putstr_fd("Error\nFichier d'entree vide !\n", 2), 1);
	map = current;
	while (current->ligne)
	{
		current->next = newchunk(get_next_line(fd));
		if (!current->next)
			return (freeallchunk(map), ft_putstr_fd("Error\nLe malloc est KC !\n",2), 1);
		current = current->next;
	}
	info = getinfo(map);
	if (!info.no.path || !info.so.path || !info.we.path || !info.ea.path \
			|| !info.f || !info.c || !info.lstmap)
		return (freelstmap(info.lstmap), freeinfo(&info), 1);
	info.map = parsemap(info.lstmap);
	if (!info.map || !isvalid(info.map, &info))
		return (freeinfo(&info), 1);
	if (mlx(&info))
		return (freeinfo(&info), 1);
	freeinfo(&info);
	return (0);
}
