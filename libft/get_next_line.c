/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <nsehnoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 11:29:15 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/14 15:52:44 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static t_gnl	*get_gnl(t_gnl **begin, const int fd)
{
	t_gnl	*tmp;

	tmp = *begin;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if ((tmp = (t_gnl*)malloc(sizeof(t_gnl))) == NULL)
		return (NULL);
	tmp->fd = fd;
	tmp->next = *begin;
	tmp->len = 0;
	if ((tmp->buff = ft_memalloc(1)) == NULL)
		return (NULL);
	tmp->stat = 1;
	*begin = tmp;
	return (tmp);
}

static t_bool	get_line(t_gnl *cur)
{
	char	buff_fix[BUFF_SIZE];
	int		lenread;
	char	*new_buff;

	if (ft_memchr(cur->buff, '\n', cur->len) != NULL)
		return (1);
	if ((lenread = read(cur->fd, buff_fix, BUFF_SIZE)) < 1)
	{
		cur->stat = lenread;
		return (1);
	}
	new_buff = ft_memalloc(cur->len + lenread);
	ft_memcpy(new_buff, cur->buff, cur->len);
	ft_memcpy(new_buff + cur->len, buff_fix, lenread);
	cur->len += lenread;
	free(cur->buff);
	cur->buff = new_buff;
	if (ft_memchr(cur->buff, '\n', cur->len) != NULL)
		return (1);
	return (0);
}

static char		*get_line_buff(t_gnl *cur)
{
	char	*ret;
	char	*mmchr;
	char	*new_buff;

	if ((mmchr = ft_memchr(cur->buff, '\n', cur->len)) == NULL)
	{
		if ((ret = ft_memalloc(cur->len + 1)) == NULL)
			return (NULL);
		ft_memcpy(ret, cur->buff, cur->len);
		cur->len = 0;
		free(cur->buff);
		cur->buff = ft_memalloc(1);
		return (ret);
	}
	if ((ret = ft_memalloc(mmchr - cur->buff + 1)) == NULL)
		return (NULL);
	ft_memcpy(ret, cur->buff, mmchr - cur->buff);
	if ((new_buff = ft_memalloc(cur->len - (mmchr - cur->buff))) == NULL)
		return (NULL);
	ft_memcpy(new_buff, cur->buff + (mmchr - cur->buff) + 1, cur->len -
			(mmchr - cur->buff));
	cur->len -= mmchr - cur->buff + 1;
	free(cur->buff);
	cur->buff = new_buff;
	return (ret);
}

static void		free_current_gnl(t_gnl **begin, t_gnl *current)
{
	t_gnl	*tmp;
	t_gnl	*tmp2;

	tmp = *begin;
	if (tmp == current)
	{
		*begin = tmp->next;
		free(tmp);
		tmp = NULL;
		return ;
	}
	while (tmp)
	{
		if (tmp->next == current)
		{
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp2);
			tmp2 = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*begin = NULL;
	t_gnl			*current;
	char			*ret;

	if (fd < 0 || line == NULL)
		return (-1);
	if ((current = get_gnl(&begin, fd)) == NULL)
		return (-1);
	while (!get_line(current))
		;
	if (current->stat == -1 || current->len == 0)
	{
		free_current_gnl(&begin, current);
		return (current->stat == -1 ? -1 : 0);
	}
	if ((ret = get_line_buff(current)) == NULL)
	{
		free_current_gnl(&begin, current);
		return (-1);
	}
	*line = ret;
	return (1);
}