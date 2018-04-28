/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 02:24:47 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/05/01 15:20:02 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char			*malloced_var;
	unsigned int	i;

	if (!(malloced_var = malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
		malloced_var[i++] = 0;
	return (malloced_var);
}
