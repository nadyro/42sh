/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:30:18 by nsehnoun          #+#    #+#             */
/*   Updated: 2017/11/27 01:45:24 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_all_stuff(char **static_tmp, char **line, char **a)
{
	int i;

	if (a == NULL)
	{
		*line = ft_strdup(*static_tmp);
		free(*static_tmp);
		*static_tmp = NULL;
	}
	else
	{
		i = ft_strchr((const char*)*static_tmp, '\n') - *static_tmp;
		*line = ft_strsub(*static_tmp, 0, i);
		*a = *static_tmp;
		*static_tmp = ft_strdup(*a + (i + 1));
		free(*a);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int				x;
	char			*a;
	char			*chr;
	static char		*static_tmp;
	char			buffer[BUFF_SIZE + 1];

	if (fd < 0 || !line)
		return (-1);
	if (!static_tmp && (!(static_tmp = ft_strnew(0))))
		return (-1);
	while (!(chr = ft_strchr((const char *)static_tmp, '\n')) &&
			(x = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[x] = '\0';
		a = static_tmp;
		static_tmp = ft_strjoin((char const*)a, (char const*)buffer);
		free(a);
	}
	if (x == -1)
		return (-1);
	if (chr)
		return (get_all_stuff(&static_tmp, line, &a));
	if (x == 0 && ft_strlen(static_tmp) > 0)
		return (get_all_stuff(&static_tmp, line, NULL));
	return (0);
}
