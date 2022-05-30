/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:54:13 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/20 11:54:35 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;
	unsigned int	j;

	i = ft_strlen(s);
	j = 0;
	if (len > i)
		len = i;
	dest = malloc(sizeof(char) * len + 1);
	if (!dest || !s)
		return (NULL);
	while (s[j])
		j++;
	i = 0;
	while (i < len && start < j)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}
