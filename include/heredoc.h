/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcanaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 18:57:57 by tcanaud           #+#    #+#             */
/*   Updated: 2018/08/02 19:08:08 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include <stdlib.h>

/*
**	t_doc:
**		here_end 	-> here end
**		len_end		-> len here end
**		doc			-> full doc
**		len_doc		-> len doc
**		next		-> next doc
*/

typedef struct			s_doc {
	char			*end;
	size_t			len_end;
	char			*doc;
	int				len_doc;
	struct s_doc	*next;
}						t_doc;

/*
**	t_dirdoc:
**		n_doc -> n doc
**		i_doc -> current doc
**		first -> first doc
*/

typedef struct			s_dirdoc {
	int		n_doc;
	int		i_doc;
	t_doc	*first;
	t_doc	*last;
}						t_dirdoc;

int						heredoc_manager(int opt);
int						heredoc_add(int *token, char *str);
int						heredoc_fill(void);
char					*heredoc_get(int id);

#endif
