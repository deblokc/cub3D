/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:09:08 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/01 12:12:25 by tnaton           ###   ########.fr       */
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

int	freeallchunk(t_map *map)
{
	t_map	*tmp;

	while (map)
	{
		tmp = map;
		map = map->next;
		free(tmp);
	}
	return (1);
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

void	freeinfo(t_info *info)
{
	free(info->f);
	free(info->c);
	free(info->no);
	free(info->so);
	free(info->we);
	free(info->ea);
	freeallchunk(info->lstmap);
	freecharchar(info->map);
}

int	ispointcub(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i < 4)
		return (0);
	if (str[i - 1] == 'b' && str[i - 2] == 'u' && str[i - 3] == 'c' \
			&& str[i - 4] == '.')
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
					printerrcoo("La map n'est pas fermee en ", i, j, info);
					isvalid = 0;
				}
			if (map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N' \
					|| map[i][j] == 'S')
			{
				if (!info->dir)
					info->dir = map[i][j];
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
			return (freeallchunk(map));
		current = current->next;
	}
	info = getinfo(map);
	if (!info.no || !info.so || !info.we || !info.ea \
			|| !info.f || !info.c || !info.lstmap)
		return (freelstmap(info.lstmap), freeinfo(&info), 1);
	info.map = parsemap(info.lstmap);
	if (!info.map || !isvalid(info.map, &info))
		return (freeinfo(&info), 1);
	printf("%s\n", info.no);
	printf("%s\n", info.so);
	printf("%s\n", info.we);
	printf("%s\n", info.ea);
	printf("%d %d %d\n", info.f[0], info.f[1], info.f[2]);
	printf("%d %d %d\n", info.c[0], info.c[1], info.c[2]);
	freeinfo(&info);
	return (0);
}
