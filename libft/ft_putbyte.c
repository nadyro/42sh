/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putbyte.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 02:28:21 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/13 04:31:37 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_putbyte(void *s, size_t len)
{
	write(STDOUT_FILENO, s, len);
}
