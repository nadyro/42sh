/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 09:53:40 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/04/13 10:41:30 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)c == s[i])
			return (((char *)s + i));
		i++;
	}
	if ((unsigned char)c == '\0')
		return (((char *)s + i));
	return (NULL);
}
