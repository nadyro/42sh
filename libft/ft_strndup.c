/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 15:05:44 by arohani           #+#    #+#             */
/*   Updated: 2018/02/19 15:51:25 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strndup(const char *s1, size_t n)
{
	char		*str;
	size_t		i;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * n + 1)))
		return (NULL);
	while (s1[i] && i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
