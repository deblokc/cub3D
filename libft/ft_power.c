/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:44:10 by tnaton            #+#    #+#             */
/*   Updated: 2021/12/01 18:18:03 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	ft_power(int nb, int pow)
{
	unsigned long long	ret;

	ret = 1;
	while (pow--)
		ret *= nb;
	return (ret);
}
