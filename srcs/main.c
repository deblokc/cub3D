/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:09:08 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/30 20:29:03 by tnaton           ###   ########.fr       */
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
	t_map *tmp;

	while (map)
	{
		free(map->ligne);
		tmp = map;
		map = map->next;
		free(tmp);
	}
	return (1);
}

int	charinstr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		if (str[i] == ' ')
			return (0);
		i++;
	}
	return (0);
}

int	substrinstr(char *str, char *substr)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		while (str[i] && str[i] != ' ' && str[i] != substr[0])
			i++;
		if (str[i] && str[i] != ' ' && str[i + 1] == substr[1])
			return (1);
		if (!str[i] || str[i] == ' ')
			return (0);
		i++;
	}
	return (0);
}

char	*getlaststr(char *ligne)
{
	int	i;

	i = 0;
	while (ligne[i] && ligne[i] == ' ')
		i++;
	while (ligne[i] && ligne[i] != ' ')
		i++;
	while (ligne[i] && ligne[i] == ' ')
		i++;
	return (ft_substr(ligne, i, ft_strlen(ligne) - i));
}

unsigned char	*getlist(char *str)
{
	int	i;
	int	j;
	unsigned char *lst;

	lst = malloc(sizeof(unsigned char) * 3);
	if (!lst)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != ',')
		i++;
	lst[0] = ft_atoi(ft_substr(str, j, i - j));
	i++;
	j = i;
	while (str[i] && str[i] != ',')
		i++;
	lst[1] = ft_atoi(ft_substr(str, j, i - j));
	i++;
	j = i;
	while (str[i] && str[i] != ',')
		i++;
	lst[2] = ft_atoi(ft_substr(str, j, i - j));
	i++;
	j = i;
	return (lst);
}

t_info	getinfo(t_map *map)
{
	t_info	info;
	t_map	*current;

	current = map;
	info.NO = NULL;
	info.SO = NULL;
	info.WE = NULL;
	info.EA = NULL;
	info.F = NULL;
	info.C = NULL;
	while (current)
	{
		if (substrinstr(current->ligne, "NO"))
			info.NO = getlaststr(current->ligne);
		else if (substrinstr(current->ligne, "SO"))
			info.SO = getlaststr(current->ligne);
		else if (substrinstr(current->ligne, "WE"))
			info.WE = getlaststr(current->ligne);
		else if (substrinstr(current->ligne, "EA"))
			info.EA = getlaststr(current->ligne);
		else if (charinstr(current->ligne, 'F'))
			info.F = getlist(getlaststr(current->ligne));
		else if (charinstr(current->ligne, 'C'))
			info.C = getlist(getlaststr(current->ligne));
		else if (ft_strcmp(ft_strtrim(current->ligne, " "), "\n"))
		{
			info.map = current;
			break;
		}
		current = current->next;
	}
	return (info);
}

int	main(int ac, char **av)
{
	t_map	*map;
	t_map	*current;
	t_info	info;
	int fd;

	if (ac != 2)
		return (ft_putstr_fd("Error\nNombre d'arg invalide !\n", 2), 1);
	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
		return (ft_putstr_fd("Error\nFichier d'entree inaccessible !\n", 2), 1);
	current = newchunk(get_next_line(fd));
	map = current;
	while (current->ligne)
	{
		current->next = newchunk(get_next_line(fd));
		if (!current->next)
			return (freeallchunk(map));
		current = current->next;
	}
	info = getinfo(map);
	printf("%s", info.NO);
	printf("%s", info.SO);
	printf("%s", info.WE);
	printf("%s", info.EA);
	printf("%d %d %d\n", info.F[0], info.F[1], info.F[2]);
	printf("%d %d %d\n", info.C[0], info.C[1], info.C[2]);
	printf("%s", info.map->ligne);
	return (0);
}
