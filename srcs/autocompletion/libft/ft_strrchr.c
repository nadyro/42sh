/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 12:45:02 by azybert           #+#    #+#             */
/*   Updated: 2017/12/04 04:43:58 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *mem;

	mem = (char *)s;
	while (*mem)
		mem++;
	while (s != mem)
		if (*(mem--) == (char)c)
			return (mem + 1);
	if ((char)c == *s)
		return (mem);
	return (NULL);
}
