/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseinfo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:01:13 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/01 11:51:35 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	charinstr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
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
	if (!str || !*str)
		return (0);
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
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (ligne[i] && ligne[i] == ' ')
		i++;
	j = i;
	while (ligne[i] && ligne[i] != ' ')
		i++;
	j = i - j;
	while (ligne[i] && ligne[i] == ' ')
		i++;
	ret = ft_substr(ligne, i, ft_strlen(ligne) - i);
	ret = ft_strtrim_free(ret, " \n");
	if (charinstr(ret, ' ') && j == 2)
		return (free(ligne), free(ret), NULL);
	return (free(ligne), ret);
}

unsigned char	*getlist(char *str)
{
	int				i;
	int				j;
	unsigned char	*lst;

	if (!str || !*str)
		return (free(str), NULL);
	lst = malloc(sizeof(unsigned char) * 3);
	if (!lst)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i] && str[i] != ',')
		i++;
	j = ft_atoi_free(ft_substr(str, j, i - j));
	if (j < 0 || j > 255)
		return (free(lst), free(str), NULL);
	lst[0] = j;
	i++;
	j = i;
	while (str[i] && str[i] != ',')
		i++;
	j = ft_atoi_free(ft_substr(str, j, i - j));
	if (j < 0 || j > 255)
		return (free(lst), free(str), NULL);
	lst[1] = j;
	i++;
	j = i;
	while (str[i] && str[i] != ',')
		i++;
	j = ft_atoi_free(ft_substr(str, j, i - j));
	if (j < 0 || j > 255)
		return (free(lst), free(str), NULL);
	lst[2] = j;
	i++;
	j = i;
	free(str);
	return (lst);
}

void	puterr(char *str, t_info *info)
{
	if (!info->printerr)
	{
		ft_putstr_fd("Error\n", 2);
		info->printerr = 1;
	}
	ft_putstr_fd(str, 2);
}

void	printerr(t_info *info)
{
	if (!info->no)
		puterr("Erreur sur la ligne NO\n", info);
	if (!info->so)
		puterr("Erreur sur la ligne SO\n", info);
	if (!info->we)
		puterr("Erreur sur la ligne WE\n", info);
	if (!info->ea)
		puterr("Erreur sur la ligne EA\n", info);
	if (!info->f)
		puterr("Erreur sur la ligne F\n", info);
	if (!info->c)
		puterr("Erreur sur la ligne C\n", info);
}

t_info	getinfo(t_map *map)
{
	t_info	info;
	t_map	*current;
	t_map	*tmp;

	current = map;
	info.no = NULL;
	info.so = NULL;
	info.we = NULL;
	info.ea = NULL;
	info.f = NULL;
	info.c = NULL;
	info.map = NULL;
	info.dir = 0;
	info.printerr = 0;
	while (current)
	{
		if (substrinstr(current->ligne, "NO"))
			info.no = getlaststr(current->ligne);
		else if (substrinstr(current->ligne, "SO"))
			info.so = getlaststr(current->ligne);
		else if (substrinstr(current->ligne, "WE"))
			info.we = getlaststr(current->ligne);
		else if (substrinstr(current->ligne, "EA"))
			info.ea = getlaststr(current->ligne);
		else if (charinstr(current->ligne, 'F'))
			info.f = getlist(getlaststr(current->ligne));
		else if (charinstr(current->ligne, 'C'))
			info.c = getlist(getlaststr(current->ligne));
		else if (ft_strcmp_free(ft_strtrim(current->ligne, " "), "\n"))
		{
			info.lstmap = current;
			break ;
		}
		else
			free(current->ligne);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	printerr(&info);
	return (info);
}
