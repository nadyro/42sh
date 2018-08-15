/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 14:13:58 by antoipom          #+#    #+#             */
/*   Updated: 2018/08/15 13:32:06 by tcanaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>
# include "sh_line_edit.h"

enum
{
	ANY = 0,
	SPACE,
	TAB,
	ESCAPE,
	DQUOTE,
	QUOTE,
	NEWLINE,
	IO_NUMBER,
	GREAT,
	LESS,
	PIPE,
	SEMI,
	COMMENT,
	AND,
	END,
	BANG
};

enum
{
	TK_WORD,
	TK_NEWLINE,
	TK_IO_NUMBER,
	TK_GREAT,
	TK_DGREAT,
	TK_GREATAND,
	TK_LESS,
	TK_DLESS,
	TK_LESSAND,
	TK_PIPE,
	TK_SEMI,
	TK_COMMENT,
	TK_SPACE,
	TK_AND_IF,
	TK_OR_IF,
	TK_END,
	TK_CMD,
	TK_FILENAME,
	TK_HISTORY
};

int						*get_tokens(char **line);
int						check_history_token(int *token, char **line);
void					history_get(int	*tko, char *str, int len);
void					*history_m(int cmd, void *ptr);
char					*history_research(int *tk, char *str, t_node *hist);
int						precheck_history_token(int *tk_arr, char **line);
void					get_tokens_loop(int *tk_arr, int i, char **line,
		int *state_to_token);
void					heredoc_fill_loop(t_dirdoc *doc,
		t_doc *doc_current, char *line, char *tmp)

#endif
