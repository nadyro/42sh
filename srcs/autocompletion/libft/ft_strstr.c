/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 12:54:25 by azybert           #+#    #+#             */
/*   Updated: 2017/12/04 04:41:58 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	char	*mem;
	char	*mem2;

	if (*little == '\0')
		return ((char *)big);
	while (*big)
	{
		if (*little == *big)
		{
			mem = (char *)big;
			mem2 = (char *)little;
			while (*mem2 && *mem2 == *mem)
			{
				mem2++;
				mem++;
			}
			if (*mem2 == '\0')
				return ((char *)big);
		}
		big++;
	}
	return (NULL);
}
