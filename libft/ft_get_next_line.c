/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 14:09:24 by arohani           #+#    #+#             */
/*   Updated: 2018/02/21 18:31:17 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_stock(char **stock, char **line, int eof)
{
	char		*tmp;

	if ((tmp = ft_strchr(*stock, '\04')))
		return (-2);
	else if (eof == 0 && (tmp = ft_strchr(*stock, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(*stock);
		*stock = ft_strdup(tmp + 1);
		tmp = NULL;
		return (1);
	}
	if (eof == 1 && ft_strlen(*stock))
	{
		*line = ft_strdup(*stock);
		ft_strdel(stock);
		return (1);
	}
	return (0);
}

static int		check_buff(char *buff, char **stock, char **line)
{
	char		*tmp;

	if ((tmp = ft_strchr(buff, '\04')))
		return (-2);
	else if ((tmp = ft_strchr(buff, '\n')))
	{
		*tmp = '\0';
		*line = (*stock) ? ft_strjoin(*stock, buff) : ft_strdup(buff);
		ft_strdel(stock);
		*stock = (tmp + 1) ? ft_strdup(tmp + 1) : NULL;
		tmp = NULL;
		ft_strdel(&buff);
		return (1);
	}
	return (0);
}

static int		handle_errors(int ret)
{
	if (ret == 0)
		return (-2);
	else
		return (-1);
}

int				ft_get_next_line(const int fd, char **line)
{
	static char	*stock = NULL;
	char		*buff;
	int			ret;
	char		*tmp;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (stock && (check_stock(&stock, line, 0)))
		return (1);
	buff = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (check_buff(buff, &stock, line))
			return (1);
		tmp = (stock) ? ft_strjoin(stock, buff) : ft_strdup(buff);
		free(stock);
		stock = tmp;
	}
	ft_strdel(&buff);
	if (ret == 0 || ret == -1)
		return (handle_errors(ret));
	if (stock && (check_stock(&stock, line, 1)))
		return (1);
	return (0);
}
