/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 13:18:45 by arohani           #+#    #+#             */
/*   Updated: 2017/04/29 14:21:31 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_digits(int n)
{
	static long	tmp;
	static int	count;

	tmp = n;
	count = 0;
	if (n == 0)
		count = 1;
	if (n < 0)
		tmp = -n;
	while (tmp > 0)
	{
		count++;
		tmp /= 10;
	}
	if (n < 0)
		count++;
	if (n == -2147483648)
		count = 11;
	return (count);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		count;
	long	nb;

	nb = n;
	count = ft_digits(n);
	if (!(str = (char *)malloc(sizeof(*str) * count + 1)))
		return (NULL);
	str[count] = '\0';
	if (n == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[count - 1] = (nb % 10) + '0';
		nb /= 10;
		count--;
	}
	return (str);
}
