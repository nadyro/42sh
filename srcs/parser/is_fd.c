/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 17:13:07 by arohani           #+#    #+#             */
/*   Updated: 2018/08/12 13:24:37 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static int		is_alldigit(char *str, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int				is_fd(char *str, int len, t_shell *shell)
{
	int		i;
	char	*buffer;
	int		fd;

	i = 0;
	if (is_alldigit(str, len) == 0)
		return (0);
	buffer = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_bzero(buffer, ft_strlen(str) + 1);
	ft_strncpy(buffer, str, len);
	fd = ft_atoi(buffer);
	if (fcntl(fd, F_GETFD) == -1)
	{
		free(buffer);
		ft_putnbr_fd(fd, 2);
		ft_putendl_fd(": Bad file descriptor", 2);
		shell->redir_error = 1;
		return (-1);
	}
	fd = ft_atoi(buffer);
	free(buffer);
	return (fd);
}
