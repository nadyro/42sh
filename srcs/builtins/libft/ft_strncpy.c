/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 14:35:38 by arohani           #+#    #+#             */
/*   Updated: 2017/05/08 15:13:21 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (src[i] != '\0' && len > 0)
	{
		dst[i] = src[i];
		i++;
		len--;
	}
	while (len > 0)
	{
		dst[i] = '\0';
		i++;
		len--;
	}
	return (dst);
}
