/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:10:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/31 20:02:07 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigitstr(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atoi_free(char *nptr)
{
	int			i;
	long long	nbr;

	i = 0;
	nbr = 0;
	nptr = ft_strtrim_free(nptr, " ");
	if (nptr[i] && nptr[i] == '+')
		i++;
	if (!ft_isdigitstr(nptr + i))
		return (free(nptr), -1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((nbr * -1) < -2147483648)
			return (nbr);
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (free(nptr), nbr);
}
