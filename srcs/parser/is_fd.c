/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 17:13:07 by arohani           #+#    #+#             */
/*   Updated: 2018/08/01 12:05:19 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static int		is_alldigit(char *str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int				is_fd(char *str, int len)	//receives token after redirect to check if fd or filename
{
	int		i;
    char	*buffer;
    int     fd;

	i = 0;
	if (is_alldigit(str, len) == 0)
		return (0);
	buffer = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_bzero(buffer, ft_strlen(str) + 1);
	ft_strncpy(buffer, str, len);
	//printf("in is_fd, buffer = %s\n", buffer);
	if (fcntl(ft_atoi(buffer), F_GETFD) == -1)
	{
		free(buffer);
		ft_putendl_fd("Bad file descriptor", 2);
		return (-1);
    }
    fd = ft_atoi(buffer);
	free(buffer);
	return (fd);
}