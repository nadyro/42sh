/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 13:14:34 by azybert           #+#    #+#             */
/*   Updated: 2017/12/04 01:12:02 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*tmp;

	tmp = dst;
	if (dst < src)
		while (len--)
			*(char *)(dst++) = *(char *)(src++);
	else
		while (len--)
			*(char *)(dst + len) = *(char *)(src + len);
	return (tmp);
}
