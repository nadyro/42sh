/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 14:35:10 by azybert           #+#    #+#             */
/*   Updated: 2017/12/04 03:56:23 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*mem;

	if (f == NULL || !(mem = ft_strdup(s)))
		return (NULL);
	i = -1;
	while (s[++i])
		mem[i] = f(i, s[i]);
	return (mem);
}
