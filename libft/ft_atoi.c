/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 05:07:13 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/04/28 12:23:58 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int to_int;
	int is_n;

	i = 0;
	is_n = 1;
	to_int = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		is_n = -1;
		i++;
	}
	(str[i] == '+' && is_n == 1) ? i++ : i;
	if (str[i] == '\0')
		return (0);
	while (ft_isdigit(str[i]))
	{
		to_int *= 10;
		to_int += ((str[i] - '0') % 10);
		i++;
	}
	return (to_int * is_n);
}
