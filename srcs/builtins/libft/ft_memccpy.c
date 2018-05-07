/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 16:06:24 by arohani           #+#    #+#             */
/*   Updated: 2017/04/27 13:25:07 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	unsigned char		uc;

	d = dst;
	s = src;
	uc = c;
	while (n > 0)
	{
		if ((*d++ = *s++) == uc)
			return (d);
		n--;
	}
	return (0);
}
