/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseinfo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:01:13 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/15 14:46:49 by tnaton           ###   ########.fr       */
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
		if (info->f < 0)
			puterr("Erreur sur la ligne F\n", info);
		if (info->c < 0)
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
	else if (charinstr(current->ligne, 'F') && info->f == -1)
		info->f = getlist(getlaststr(current->ligne));
	else if (charinstr(current->ligne, 'C') && info->c == -1)
		info->c = getlist(getlaststr(current->ligne));
	else if (charinstr(current->ligne, 'D') && !info->door.path)
		info->door.path = getlaststr(current->ligne);
	else if (charinstr(current->ligne, 'X') && !info->exit.path)
		info->exit.path = getlaststr(current->ligne);
	else if (!substrinstr(current->ligne, "WE") \
			&& !substrinstr(current->ligne, "EA") \
			&& charinstr(current->ligne, 'E') && !info->end.path)
		info->end.path = getlaststr(current->ligne);
	else
		return (0);
	return (1);
}

int	ischiant(t_map *current)
{
	return (substrinstr(current->ligne, "NO")
		|| substrinstr(current->ligne, "SO")
		|| substrinstr(current->ligne, "WE")
		|| substrinstr(current->ligne, "EA")
		|| charinstr(current->ligne, 'F')
		|| charinstr(current->ligne, 'C'));
}

t_info	errdeligne(t_info info, t_map *current)
{
	return (puterr("Cette ligne est en trop : ", &info), \
			ft_putstr_fd(current->ligne, 2), \
			freelstmap(current), \
			freeallchunk(current), info);
}

int	fl(char *str, t_info *info)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ischr(str[i]) && str[i] != '\n')
		{
			info->isvalid = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

t_info	getinfo(t_map *current)
{
	t_info	info;
	t_map	*tmp;

	initinfo(&info);
	while (current)
	{
		if (getlineinfo(current, &info))
			info.dir = 0;
		else if (ischiant(current))
			return (errdeligne(info, current));
		else if (ft_strcmp_free(ft_strtrim(current->ligne, " "), "\n"))
		{
			if (!fl(current->ligne, &info))
				puterr("Ligne de map invalide !\n", &info);
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
