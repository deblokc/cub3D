/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseinfo2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:14:13 by tnaton            #+#    #+#             */
/*   Updated: 2022/06/15 14:48:43 by tnaton           ###   ########.fr       */
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
		{
			if (str[i + 1] == ' ')
				return (1);
			return (0);
		}
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
			i++;
		if (!str[i] || str[i] == ' ')
			return (0);
		if (!str[i + 1] || str[i + 1] != ' ')
			return (0);
		return (1);
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

int	getlist(char *str)
{
	unsigned int	i;
	unsigned int	j;
	int				k;
	unsigned char	*lst;

	k = 0;
	lst = malloc(sizeof(unsigned char) * 3);
	if (!lst || !str || !*str)
		return (free(lst), free(str), -2);
	i = 0;
	j = 0;
	while (k < 3)
	{
		j = i;
		while (str[i] && str[i] != ',')
			i++;
		j = ft_atoi_free(ft_substr(str, j, i - j));
		if (j > 255)
			return (free(lst), free(str), -2);
		lst[k] = (unsigned char)j;
		i++;
		k++;
	}
	j = (((lst[0] & 0x0ff) << 16) | ((lst[1] & 0x0ff) << 8) | (lst[2] & 0x0ff));
	return (free(str), free(lst), j);
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
