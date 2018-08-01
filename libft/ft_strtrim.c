/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 16:53:09 by azybert           #+#    #+#             */
/*   Updated: 2018/07/20 10:08:56 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*start;
	char	*end;

	if (s == NULL)
		return (NULL);
	start = (char *)s;
	while (*start && (*start == ' ' || *start == '\n' || *start == '\t'))
		start++;
	end = (char *)start;
	while (*end)
		end++;
	end--;
	while (end >= start && (*end == ' ' || *end == '\n' || *end == '\t'))
		end--;
	return (ft_strndup(start, end - start + 1));
}
