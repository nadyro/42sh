/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 19:06:37 by azybert           #+#    #+#             */
/*   Updated: 2018/08/15 13:00:55 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char	*tmp;

	if (dst == NULL || src == NULL)
		return (NULL);
	tmp = dst;
	while (*src)
		*(tmp++) = *(src++);
	*tmp = '\0';
	return (dst);
}
