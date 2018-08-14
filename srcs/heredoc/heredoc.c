/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 05:41:54 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/14 16:25:11 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "sh_line_edit.h"
#include "libft.h"

static t_dirdoc		g_dir;

/*
** opt:
** 	0	-> heredoc_init
**	1	-> heredoc_isopen
**	2	-> heredoc_clear
*/

int					heredoc_manager(int opt)
{
	t_doc	*tmp;
	t_doc	*tmp2;

	if (opt == 0)
		ft_bzero(&g_dir, sizeof(t_dirdoc));
	else if (opt == 1)
		return (g_dir.n_doc);
	else if (opt == 2)
	{
		tmp = g_dir.first;
		while (tmp)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			free(tmp2->end);
			free(tmp2->doc);
			free(tmp2);
		}
		heredoc_manager(0);
	}
	return (0);
}

int					heredoc_add(int *token, char *str)
{
	t_doc	*new;

	if ((new = (t_doc*)malloc(sizeof(t_doc))) == NULL)
		return (1);
	if ((new->end = ft_strndup(str + token[1], token[2])) == NULL)
	{
		free(new);
		return (1);
	}
	new->len_end = token[2];
	new->doc = NULL;
	new->len_doc = 0;
	new->next = NULL;
	(g_dir.last == NULL) ? (g_dir.first = new) :
		(g_dir.last->next = new);
	g_dir.last = new;
	g_dir.n_doc += 1;
	return (0);
}

char				*heredoc_get(int id)
{
	int		i;
	t_doc	*tmp;

	if (id >= g_dir.n_doc)
		return (NULL);
	i = 0;
	tmp = g_dir.first;
	while (tmp && i < id)
	{
		tmp = tmp->next;
		i++;
	}
	if (i != id)
		return (NULL);
	return (tmp->doc);
}

static t_doc		*heredoc_get_doc(int id)
{
	int		i;
	t_doc	*tmp;

	if (id >= g_dir.n_doc)
		return (NULL);
	i = 0;
	tmp = g_dir.first;
	while (tmp && i < id)
	{
		tmp = tmp->next;
		i++;
	}
	if (i != id)
		return (NULL);
	return (tmp);
}

int					heredoc_fill(void)
{
	char	*line;
	t_doc	*doc_current;
	char	*tmp;

	while (g_dir.i_doc != g_dir.n_doc)
	{
		doc_current = heredoc_get_doc(g_dir.i_doc);
		line = line_edit_main_loop("> ", NULL);
		if (ft_strlen(line) - 1 == doc_current->len_end
				&& !ft_memcmp(line, doc_current->end, doc_current->len_end))
			g_dir.i_doc += 1;
		else
		{
			if (doc_current->doc == NULL)
				doc_current->doc = ft_strdup(line);
			else
			{
				tmp = doc_current->doc;
				doc_current->doc = ft_strjoin(doc_current->doc, line);
				free(tmp);
			}
			doc_current->len_doc = ft_strlen(doc_current->doc);
		}
		free(line);
	}
	return (0);
}
