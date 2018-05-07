/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 15:02:16 by arohani           #+#    #+#             */
/*   Updated: 2017/04/27 15:29:18 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_strnlen(const char *str, size_t n)
{
	static size_t i;

	i = 0;
	while (i < n && str[i] != '\0')
		i++;
	return (i);
}

char				*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*d;
	size_t	len;

	d = s1;
	s1 += ft_strlen(s1);
	len = ft_strnlen(s2, n);
	s1[len] = '\0';
	ft_strncpy(s1, s2, len);
	return (d);
}
