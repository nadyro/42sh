/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 23:04:31 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/04/28 20:42:47 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*str_dst;
	const char	*str_src;
	size_t		i;
	size_t		dst_len;

	str_dst = dst;
	str_src = src;
	i = size;
	while (i-- != 0 && *str_dst != '\0')
		str_dst++;
	dst_len = str_dst - dst;
	i = size - dst_len;
	if (i == 0)
		return (dst_len + (ft_strlen(str_src)));
	while (*str_src)
	{
		if (i != 1)
		{
			*str_dst++ = *str_src;
			i--;
		}
		str_src++;
	}
	*str_dst = '\0';
	return (dst_len + (str_src - src));
}
