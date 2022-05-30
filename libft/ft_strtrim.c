/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:22:26 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/21 12:39:09 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinstr(char const *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*dest;

	i = ft_strlen(s1);
	j = 0;
	k = 0;
	while (i > 0 && ft_isinstr(set, s1[i - 1]))
		i--;
	while (j < i && s1[j] && ft_isinstr(set, s1[j]))
		j++;
	dest = malloc(sizeof(char) * (i - j) + 1);
	if (!dest)
		return (NULL);
	while (j < i)
		dest[k++] = s1[j++];
	dest[k] = '\0';
	return (dest);
}
