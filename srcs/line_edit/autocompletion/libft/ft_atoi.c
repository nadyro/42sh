/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 13:54:15 by azybert           #+#    #+#             */
/*   Updated: 2018/01/27 20:21:22 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int num;
	int neg;

	num = 0;
	while (ft_isspace(*str))
		str++;
	neg = (*str == '-' ? 1 : 0);
	str = (*str == '+' || *str == '-' ? str + 1 : str);
	while (*str && *str >= '0' && *str <= '9')
		num = num * 10 - (*(str++) - '0');
	return (num = (neg ? num : -num));
}
