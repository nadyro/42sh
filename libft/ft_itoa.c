/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 14:57:04 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 15:25:07 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strrev_itoa(char *s)
{
	int		i;
	size_t	y;
	char	c;
	char	*str_s;

	i = 0;
	c = s[i];
	y = ft_strlen(s) - 1;
	if (!(str_s = ft_strnew(y + 1)))
		return (NULL);
	while ((int)y > 0)
	{
		if (s[i] == '-')
		{
			str_s[i] = '-';
			i++;
		}
		str_s[i] = s[y];
		i++;
		y--;
	}
	str_s[i] = (c != '-' ? s[y] : '\0');
	return (str_s);
}

static char	*ft_fillstr(size_t z, int y)
{
	char	*str;
	int		x;
	int		i;

	i = 0;
	x = 0;
	if (y < 0)
	{
		if (!(str = ft_strnew((z + 1))))
			return (NULL);
		y = y * -1;
		str[0] = '-';
		x++;
	}
	else if (!(str = ft_strnew(z)))
		return (NULL);
	while (y >= 10)
	{
		i = y % 10;
		y = y / 10;
		str[x] = i + '0';
		x++;
	}
	str[x] = y + '0';
	return (str);
}

char		*ft_itoa(int n)
{
	int		y;
	size_t	z;
	char	*str;

	z = 1;
	y = n;
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		else
			n = n * -1;
	}
	while (n >= 10)
	{
		n = n / 10;
		z++;
	}
	if (!(str = ft_fillstr(z, y)))
		return (NULL);
	return (!(ft_strrev_itoa(str))) ? NULL : ft_strrev_itoa(str);
}
