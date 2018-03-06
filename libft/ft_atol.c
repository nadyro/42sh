/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 13:54:15 by azybert           #+#    #+#             */
/*   Updated: 2017/12/04 05:10:49 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atol(const char *str)
{
	long int	num;
	int			neg;

	num = 0;
	while (ft_isspace(*str))
		str++;
	neg = (*str == '-' ? 1 : 0);
	str = (*str == '+' || *str == '-' ? str + 1 : str);
	while (*str && *str >= '0' && *str <= '9')
		num = num * 10 - (*(str++) - '0');
	return (num = (neg ? num : -num));
}
