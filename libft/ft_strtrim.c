/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 11:54:30 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 15:23:52 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	y;
	char	*str_s;

	if (s != NULL)
	{
		i = 0;
		y = 0;
		while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
			i++;
		if (s[i] == '\0')
			return (ft_strdup(""));
		y = i;
		i = ft_strlen(s) - 1;
		while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
			i--;
		if (!(str_s = ft_strsub(s, y, (i - y) + 1)))
			return (NULL);
		return (str_s);
	}
	return (NULL);
}
