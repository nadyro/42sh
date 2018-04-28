/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 10:44:38 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/04/13 11:35:38 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if ((unsigned char)c == str[i])
			return ((char *)str + i);
		i--;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str + ft_strlen(str));
	return (NULL);
}
