/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 11:36:02 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/04/28 14:22:05 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;
	size_t y;

	i = 0;
	y = 1;
	if (n == 0)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i] && y < n)
	{
		i++;
		y++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
