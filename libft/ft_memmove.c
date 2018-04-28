/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 04:22:31 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/04/24 12:24:53 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*str_src;
	char		*str_dst;

	str_src = src;
	str_dst = dst;
	if (str_src >= str_dst || (size_t)(str_dst - str_src) >= len)
		return (ft_memcpy(dst, src, len));
	else
	{
		str_dst += len;
		str_src += len;
		while (len--)
			*(--str_dst) = *(--str_src);
	}
	return (dst);
}
