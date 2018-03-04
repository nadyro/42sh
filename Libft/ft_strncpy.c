/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 19:39:15 by azybert           #+#    #+#             */
/*   Updated: 2018/02/04 00:02:19 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*tmp;

	tmp = dst;
	while (*src && len)
	{
		*(tmp++) = *(src++);
		len--;
	}
	while (len--)
		*(tmp++) = '\0';
	return (dst);
}
