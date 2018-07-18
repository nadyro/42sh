/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 12:54:25 by azybert           #+#    #+#             */
/*   Updated: 2017/12/04 04:38:55 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*mem;
	char	*mem2;
	int		mem3;

	if (*little == '\0')
		return ((char *)big);
	while (*big && len)
	{
		if (*little == *big)
		{
			mem = (char *)big;
			mem2 = (char *)little;
			mem3 = len;
			while (*mem2 != '\0' && *mem2 == *mem && mem3--)
			{
				mem2++;
				mem++;
			}
			if (*mem2 == '\0')
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
