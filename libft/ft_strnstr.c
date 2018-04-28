/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:46:57 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 14:04:55 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t y;

	i = 0;
	y = 0;
	if (little[y] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		y = 0;
		while (big[i + y] == little[y] && (i + y) <= len)
		{
			y++;
			if (little[y] == '\0')
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
