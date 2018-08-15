/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <tcanaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 13:22:15 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/15 15:19:24 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "sh_line_edit.h"
#include "libft.h"

static t_doc		*heredoc_get_doc(t_dirdoc *doc, int id)
{
	int		i;
	t_doc	*tmp;

	if (id >= doc->n_doc)
		return (NULL);
	i = 0;
	tmp = doc->first;
	while (tmp && i < id)
	{
		tmp = tmp->next;
		i++;
	}
	if (i != id)
		return (NULL);
	return (tmp);
}

void	heredoc_fill_loop(t_dirdoc *doc,
		t_doc *doc_current, char *line, char *tmp)
{
	doc_current = heredoc_get_doc(doc, doc->i_doc);
	line = line_edit_main_loop("> ", NULL, 0);
	if (ft_strlen(line) - 1 == doc_current->len_end
			&& !ft_memcmp(line, doc_current->end, doc_current->len_end))
		doc->i_doc += 1;
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
