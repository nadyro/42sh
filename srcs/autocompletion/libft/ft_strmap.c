/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 14:35:10 by azybert           #+#    #+#             */
/*   Updated: 2017/12/04 03:55:51 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*mem;

	if (f == NULL || !(mem = ft_strdup(s)))
		return (NULL);
	i = -1;
	while (s[++i])
		mem[i] = f(s[i]);
	return (mem);
}
