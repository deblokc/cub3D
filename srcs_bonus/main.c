/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:09:08 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/09 13:37:26 by bdetune          ###   ########.fr       */
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

t_map	*getcurrent(char *path)
{
	t_map	*current;
	t_map	*map;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
		return (ft_putstr_fd("Error\nFichier d'entree inaccessible !\n", 2), \
				NULL);
	current = newchunk(get_next_line(fd));
	if (!current->ligne)
		return (free(current), \
				ft_putstr_fd("Error\nFichier d'entree vide !\n", 2), NULL);
	map = current;
	while (current->ligne)
	{
		current->next = newchunk(get_next_line(fd));
		if (!current->next)
			return (freeallchunk(map), \
					ft_putstr_fd("Error\nLe malloc est KC !\n", 2), NULL);
		current = current->next;
	}
	return (map);
}

int	main(int ac, char **av)
{
	t_map	*map;
	t_info	info;

	if (ac != 2)
		return (ft_putstr_fd("Error\nNombre d'arg invalide !\n", 2), 1);
	if (!ispointcub(av[1]))
		return (ft_putstr_fd("Error\nExtension invalide !\n", 2), 1);
	map = getcurrent(av[1]);
	if (!map)
		return (1);
	info = getinfo(map);
	if (!info.no.path || !info.so.path || !info.we.path || !info.ea.path \
			|| info.f < 0 || info.c < 0 || !info.lstmap)
		return (freelstmap(info.lstmap), freeinfo(&info), 1);
	info.map = parsemap(info.lstmap);
	if (info.doors && add_door_text(&info))
		return (freeinfo(&info), 1);
	if (!info.map || !isvalid(info.map, &info))
		return (freeinfo(&info), 1);
	if (mlx(&info))
		return (freeinfo(&info), 1);
	freeinfo(&info);
	return (0);
}
