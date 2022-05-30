/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:56:06 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/05 14:34:36 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s || !*s)
		return (-1);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count + 1);
}

static void	ft_free(char **list, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(list[i++]);
	free(list);
}

char	**ft_split(char *s, char c)
{
	char	**dest;
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	end = 0;
	if (!s)
		return (NULL);
	dest = NULL;
	dest = (char **)ft_calloc(sizeof(char *), count_word(s, c));
	if (!dest)
		return (NULL);
	while ((i + 1) < count_word(s, c))
	{
		while (s[end] && s[end] == c)
			end++;
		start = end;
		while (s[end] && s[end] != c)
			end++;
		dest[i++] = ft_substr(s, start, (end - start));
		if (!dest[i - 1])
			return (ft_free(dest, (i - 1)), NULL);
	}
	return (dest);
}
