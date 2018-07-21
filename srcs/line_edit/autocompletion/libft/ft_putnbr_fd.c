/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 20:39:20 by azybert           #+#    #+#             */
/*   Updated: 2018/03/07 17:13:26 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	char	mem[12];
	int		tmp;
	size_t	i;

	i = 0;
	if (n >= 0)
		n = -n;
	else
		mem[i++] = '-';
	tmp = -1;
	while (n / 10 <= tmp)
		tmp *= 10;
	while (tmp < 0)
	{
		mem[i++] = n / tmp + '0';
		n = n - n / tmp * tmp;
		tmp = tmp / 10;
	}
	mem[i] = '\0';
	write(fd, mem, ft_strlen(mem));
}
