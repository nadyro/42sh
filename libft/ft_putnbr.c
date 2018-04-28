/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 20:33:47 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 15:27:49 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr(int n)
{
	unsigned int n_2;

	if (n < 0)
	{
		n_2 = -n;
		ft_putchar('-');
	}
	else
		n_2 = n;
	if (n_2 >= 10)
	{
		ft_putnbr(n_2 / 10);
		ft_putnbr(n_2 % 10);
	}
	else
		ft_putchar(48 + n_2);
}
