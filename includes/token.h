/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <antoipom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:34:52 by antoipom          #+#    #+#             */
/*   Updated: 2018/03/30 15:38:31 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

enum
{
	TK_WORD,
	TK_ASSIGNMENT_WORD,
	TK_NAME,
	TK_NEWLINE,
	TK_IO_NUMBER,
	TK_LESS,
	TK_GREAT,
	TK_SEMI,
	TK_PIPE,
	TK_AND,
	TK_AND_IF,
	TK_OR_IF,
	TK_DSEMI,
	TK_DLESS,
	TK_DGREAT,
	TK_LESSAND,
	TK_GREATAND,
	TK_LESSGREAT,
	TK_DLESSDASH,
	TK_CLOBBER,
	TK_IF,
	TK_THEN,
	TK_ELSE,
	TK_ELIF,
	TK_FI,
	TK_DO,
	TK_DONE,
	TK_CASE,
	TK_ESAC,
	TK_WHILE,
	TK_UNTIL,
	TK_FOR,
	TK_LBRACE,
	TK_RBRACE,
	TK_BANG,
	TK_LPAREN,
	TK_RPAREN,
	TK_IN,
	TK_DOLLAR
};

#endif
