/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 15:48:08 by azybert           #+#    #+#             */
/*   Updated: 2017/12/04 04:13:25 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if ((!s1 && !s2) || (n == 0))
		return (1);
	if (!s1 || !s2)
		return (0);
	while ((*s1 || *s2) && n--)
		if (*(s1++) != *(s2++))
			return (0);
	return (1);
}