/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseinfo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:01:13 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/15 16:01:52 by bdetune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	printerr(t_info *info)
{
	if (info->isvalid)
	{
		if (!info->no.path)
			puterr("Erreur sur la ligne NO\n", info);
		if (!info->so.path)
			puterr("Erreur sur la ligne SO\n", info);
		if (!info->we.path)
			puterr("Erreur sur la ligne WE\n", info);
		if (!info->ea.path)
			puterr("Erreur sur la ligne EA\n", info);
		if (info->f == -1)
			puterr("Erreur sur la ligne F\n", info);
		if (info->c == -1)
			puterr("Erreur sur la ligne C\n", info);
	}
}

int	getlineinfo(t_map *current, t_info *info)
{
	if (substrinstr(current->ligne, "NO") && !info->no.path)
		info->no.path = getlaststr(current->ligne);
	else if (substrinstr(current->ligne, "SO") && !info->so.path)
		info->so.path = getlaststr(current->ligne);
	else if (substrinstr(current->ligne, "WE") && !info->we.path)
		info->we.path = getlaststr(current->ligne);
	else if (substrinstr(current->ligne, "EA") && !info->ea.path)
		info->ea.path = getlaststr(current->ligne);
	else if (charinstr(current->ligne, 'F') && info->f == -2)
		info->f = getlist(getlaststr(current->ligne));
	else if (charinstr(current->ligne, 'C') && info->c == -2)
		info->c = getlist(getlaststr(current->ligne));
	else
		return (0);
	return (1);
}

int	ischiant(t_map *current)
{
	return (substrinstr(current->ligne, "NO") || \
				substrinstr(current->ligne, "SO") || \
				substrinstr(current->ligne, "WE") || \
				substrinstr(current->ligne, "EA") || \
				charinstr(current->ligne, 'F') || \
				charinstr(current->ligne, 'C'));
}

int	checkline(char *line, t_info *info)
{
	int	i;

	i = 0;
	info->isvalid = 1;
	while (line[i])
	{
		if (!ischr(line[i]) && line[i] != '\n' && line[i] != ' ')
		{
			puterr("Invalide char in first line of map\n", info);
			info->isvalid = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

t_info	getinfo(t_map *map)
{
	t_info	info;
	t_map	*current;
	t_map	*tmp;

	current = map;
	initinfo(&info);
	while (current)
	{
		if (getlineinfo(current, &info))
			info.dir = 0;
		else if (ischiant(current))
			return (errdeligne(info, current));
		else if (ft_strcmp_free(ft_strtrim(current->ligne, " "), "\n"))
		{
			checkline(current->ligne, &info);
			info.lstmap = current;
			break ;
		}
		else
			free(current->ligne);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	return (printerr(&info), info);
}
