/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:12:05 by arohani           #+#    #+#             */
/*   Updated: 2018/02/16 15:24:29 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (small[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i <= len)
	{
		j = 0;
		while (big[i + j] == small[j])
		{
			j++;
			if (small[j] == '\0' && (i + j) <= len)
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
