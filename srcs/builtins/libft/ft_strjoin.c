/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 15:33:15 by arohani           #+#    #+#             */
/*   Updated: 2017/04/27 16:05:42 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*fresh;

	if (s1 && s2)
	{
		len = ft_strlen((const char *)s1) + ft_strlen((const char *)s2) + 1;
		if (!(fresh = (char *)malloc(sizeof(*fresh) * (len + 1))))
			return (NULL);
		ft_strcpy(fresh, s1);
		ft_strcat(fresh, s2);
		return (fresh);
	}
	return (0);
}
