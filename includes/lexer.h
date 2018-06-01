/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 14:13:58 by antoipom          #+#    #+#             */
/*   Updated: 2018/06/01 16:24:00 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
	TK_AND,
	TK_AND_IF,
	TK_OR_IF,
	TK_END
};

int						*get_tokens(char *line);

#endif
