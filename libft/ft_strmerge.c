/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:06:06 by azybert           #+#    #+#             */
/*   Updated: 2017/10/27 18:06:49 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmerge(char **to_merge)
{
	int		loop;
	int		length;
	char	*new_str;

	loop = -1;
	length = 0;
	while (to_merge[++loop] != NULL)
		length += ft_strlen(to_merge[loop]);
	if ((new_str = (char *)malloc(sizeof(char) * (length + 1))) == NULL)
		return (NULL);
	new_str[length] = '\0';
	while (--loop != -1)
	{
		length -= ft_strlen(to_merge[loop]);
		ft_strncpy(&new_str[length], to_merge[loop], ft_strlen(to_merge[loop]));
	}
	return (new_str);
}
