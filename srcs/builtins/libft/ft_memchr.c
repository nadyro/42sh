/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:49:06 by arohani           #+#    #+#             */
/*   Updated: 2017/04/24 19:08:16 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char uc;

	uc = c;
	while (n > 0)
	{
		if (*(unsigned char *)s == uc)
			return ((void *)s);
		s++;
		n--;
	}
	return (NULL);
}
