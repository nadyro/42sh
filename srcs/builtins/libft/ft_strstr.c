/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 16:13:30 by arohani           #+#    #+#             */
/*   Updated: 2018/02/16 15:24:24 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *small)
{
	int i;
	int j;

	i = 0;
	if (small[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == small[j])
		{
			j++;
			if (small[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
