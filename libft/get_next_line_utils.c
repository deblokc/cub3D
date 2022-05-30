/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 10:56:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/02/09 12:14:34 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return (0);
}

char	*gnl_strjoin(char *str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if (!str)
	{
		str = (char *)malloc(1 * sizeof(char));
		str[0] = '\0';
	}
	if (!str || !buff)
		return (NULL);
	dest = malloc(sizeof(char) * (gnl_strlen(str) + gnl_strlen(buff) + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = 0;
	if (str)
		while (str[++i])
			dest[i] = str[i];
	while (buff[j])
		dest[i++] = buff[j++];
	dest[gnl_strlen(str) + gnl_strlen(buff)] = '\0';
	free(str);
	return (dest);
}
