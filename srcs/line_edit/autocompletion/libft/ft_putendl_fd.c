/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 20:32:48 by azybert           #+#    #+#             */
/*   Updated: 2018/01/27 23:00:38 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	if (s == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
