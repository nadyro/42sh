/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 21:09:03 by azybert           #+#    #+#             */
/*   Updated: 2017/12/04 03:07:48 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*(s))
		if (*s++ == (char)c)
			return ((char *)s - 1);
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
