/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <antoipom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:34:52 by antoipom          #+#    #+#             */
/*   Updated: 2018/04/10 14:00:36 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>

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
	END
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
	TK_END
};

int						*get_tokens(char *line);
int						*lexer_alloc(int *tk_tab, int *tab_size);

#endif
