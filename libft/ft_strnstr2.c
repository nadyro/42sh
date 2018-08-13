/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 18:54:18 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/12 18:54:20 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr2(const char *big, const char *little, size_t len)
{
	char	*mem;
	char	*mem2;
	int		mem3;

	if (*little == '\0' || len == 0)
		return (NULL);
	while (*big)
	{
		if (*little == *big)
		{
			mem = (char *)big;
			mem2 = (char *)little;
			mem3 = len;
			while (*mem && *mem2 == *mem && len > 0)
			{
				mem2++;
				mem++;
				mem3--;
			}
			if (!mem3)
				return ((char*)big);
		}
		big++;
	}
	return (NULL);
}
