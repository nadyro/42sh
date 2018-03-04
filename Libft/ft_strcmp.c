/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 23:06:07 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/03/04 18:06:26 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 == *str2++)
	{
		if (*str1++ == '\0')
			return (0);
	}
	return (*(const unsigned char *)str1 - *(const unsigned char *)(str2 - 1));
}
