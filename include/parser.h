/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:27:44 by arohani           #+#    #+#             */
/*   Updated: 2018/06/14 18:14:55 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <builtins.h>

typedef struct	s_ast
{
	int						*tok;
	int						v1;
	int						v2;
	char					*arg;
	int						split_by;
	int						depth;
	struct s_ast			*parent;
	struct s_ast			*left;
	struct s_ast			*right;
}				t_ast;

int			parser_validation(int *tk_arr);
t_ast	    *get_ast(char ***argv);
int         ast_evaluate(t_ast *ast, t_shell *shell);
t_ast		*fill_leftast(t_ast *parent, int size);
t_ast		*fill_rightast(t_ast *parent, int start, int size);
t_ast		*init_ast(char ***argv);

#endif
