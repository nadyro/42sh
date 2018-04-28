/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 00:51:34 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/04/28 12:06:33 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str_s1;
	const unsigned char	*str_s2;

	i = 1;
	str_s1 = s1;
	str_s2 = s2;
	if (n == 0)
		return (0);
	while (*str_s1 == *str_s2 && i < n && str_s1++ && str_s2++)
		i++;
	return ((const unsigned char)*str_s1 - (const unsigned char)*str_s2);
}
