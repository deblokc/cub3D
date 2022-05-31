/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:09:49 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/31 15:57:24 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	lenof(t_map *lstmap)
{
	int	i;

	i = 0;
	while (lstmap)
	{
		lstmap = lstmap->next;
		i++;
	}
	return (i);
}

int	ft_strlen_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\n')
		i++;
	return (i);
}

int	getmaxlen(t_map *lstmap)
{
	int	max;

	max = 0;
	while (lstmap->ligne)
	{
		if (ft_strlen_map(lstmap->ligne) > max)
			max = ft_strlen_map(lstmap->ligne);
		lstmap = lstmap->next;
	}
	return (max);
}

char	*semitrim(char *str)
{
	int		i;
	char	*ret;

	str = ft_strtrim_free(str, "\n");
	i = ft_strlen(str) - 1;
	while (str[i] == ' ')
		i--;
	ret = ft_substr(str, 0, i + 1);
	return (free(str), ret);
}

char	*getligne(char *str, int maxlen)
{
	char	*ret;
	int		i;

	i = 0;
	str = semitrim(str);
	ret = malloc(sizeof(char) * (maxlen + 1));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	while (i < maxlen)
		ret[i++] = ' ';
	ret[i] = '\0';
	return (free(str), ret);
}

char	**parsemap(t_map *lstmap)
{
	char	**map;
	int		maxlen;
	int		lenmap;
	int		i;

	i = 0;
	lenmap = lenof(lstmap);
	map = malloc(sizeof(char *) * (lenmap));
	if (!map)
		return (NULL);
	maxlen = getmaxlen(lstmap);
	while (lstmap->ligne)
	{
		map[i] = NULL;
		map[i] = getligne(lstmap->ligne, maxlen);
		if (!map[i])
			return (freecharchar(map), NULL);
		printf("%s\n", map[i]);
		i++;
		lstmap = lstmap->next;
	}
	map[i] = NULL;
	return (map);
}
