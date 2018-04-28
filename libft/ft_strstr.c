/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:08:22 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/04/24 08:33:07 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	size_t	y;

	i = 0;
	y = 0;
	if (little[y] == '\0')
		return ((char *)big);
	while (big[i])
	{
		y = 0;
		while (big[i + y] == little[y])
		{
			y++;
			if (little[y] == '\0')
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
