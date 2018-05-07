/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:00:19 by arohani           #+#    #+#             */
/*   Updated: 2017/04/20 11:50:49 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int result;
	int sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == '\f' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
			|| str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - '0';
		i++;
	}
	return (sign * result);
}
