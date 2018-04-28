/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:16:17 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 15:23:37 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	y;

	if (s1 != NULL && s2 != NULL)
	{
		y = ft_strlen(s1) + ft_strlen(s2);
		if (!(str = ft_strnew(y)))
			return (NULL);
		str = ft_strncpy(str, (char *)s1, ft_strlen(s1));
		str = ft_strncat(str, (char *)s2, y);
		return (str);
	}
	return (NULL);
}
