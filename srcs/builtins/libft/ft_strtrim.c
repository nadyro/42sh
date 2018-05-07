/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:10:29 by arohani           #+#    #+#             */
/*   Updated: 2017/04/27 18:08:20 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*fresh;
	int		start;
	int		end;
	int		len;
	size_t	j;

	if (s)
	{
		start = 0;
		end = (int)ft_strlen((const char *)s);
		while (s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\n')
			end--;
		while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
			start++;
		len = end - start;
		(len < 0) ? len = 0 : len;
		if (!(fresh = (char *)malloc(sizeof(*fresh) * (len + 1))))
			return (NULL);
		j = 0;
		while (start < end)
			fresh[j++] = s[start++];
		fresh[j] = '\0';
		return (fresh);
	}
	return (0);
}
