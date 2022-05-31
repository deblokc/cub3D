/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:57:11 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/31 12:29:27 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_free(char *s1, const char *s2)
{
	int		ret;
	char	*aled;

	aled = s1;
	if (!s1 || !s2)
		return (free(aled), 1);
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (free(aled), 0);
	ret = (*(unsigned char *)s1 - *(unsigned char *)--s2);
	return (free(aled), ret);
}
