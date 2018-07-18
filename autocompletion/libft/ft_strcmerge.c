/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azybert <azybert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:06:06 by azybert           #+#    #+#             */
/*   Updated: 2018/01/28 00:19:50 by azybert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcmerge(char **to_merge, char c)
{
	int		loop;
	int		length;
	char	*new_str;

	loop = -1;
	length = 0;
	while (to_merge[++loop] != NULL)
		length += ft_strlen(to_merge[loop]);
	length += loop - 1;
	if ((new_str = (char *)malloc(sizeof(char) * (length + 1))) == NULL)
		return (NULL);
	new_str[length] = '\0';
	while (--loop != -1)
	{
		length -= ft_strlen(to_merge[loop]);
		ft_strncpy(&new_str[length], to_merge[loop], ft_strlen(to_merge[loop]));
		if (length != 0)
		{
			length--;
			ft_strncpy(&new_str[length], &c, 1);
		}
	}
	return (new_str);
}
