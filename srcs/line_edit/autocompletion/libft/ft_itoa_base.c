/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:26:05 by azybert           #+#    #+#             */
/*   Updated: 2017/12/03 22:52:21 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_convert(char *nbr, int value, int magnitude, int base)
{
	while (*nbr != '\0')
	{
		while (magnitude >= value)
		{
			if (*nbr != '9')
				*nbr = *nbr + 1;
			else
				*nbr = 'A';
			value = value - magnitude;
		}
		magnitude = magnitude / base;
		nbr++;
	}
}

static int	ft_get_size(int value, int base)
{
	int	size;

	size = (value < 0 && base == 10 ? 3 : 2);
	while ((value = value / base))
		size++;
	return (size);
}

char		*ft_itoa_base(int value, int base)
{
	char	*nbr;
	int		mem;

	if (base < 2 || base > 36)
		return (NULL);
	mem = ft_get_size(value, base);
	if (!(nbr = (char *)malloc(sizeof(char) * mem)))
		return (NULL);
	ft_memset(nbr, '0', mem--);
	nbr[mem] = '\0';
	mem = ft_power(base, (value < 0 && base == 10 ? mem - 2 : mem - 1));
	if (base != 10 || value >= 0)
		ft_convert(nbr, (value > 0 ? -value : value), -mem, base);
	else
	{
		nbr[0] = '-';
		ft_convert((nbr + 1), value, -mem, base);
	}
	return (nbr);
}
