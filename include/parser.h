/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:27:44 by arohani           #+#    #+#             */
/*   Updated: 2018/07/19 17:18:49 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <builtins.h>

typedef struct	s_ast
{
	int 					beg;	//relevant start token in token table for ast node
	int 					end;	//relevant end token in token table for ast node
	int 					split;	//relevant position where split operator token was found in token table
	int						cmd_ret;
	struct s_ast			*parent;
	struct s_ast			*left;
	struct s_ast			*right;
}				t_ast;

int			parser_validation(int *tk_arr, char *ine);
int 		get_tk_end_pos(t_shell *shell);
t_ast	    *get_ast(t_shell *shell);
int         ast_evaluate(t_ast *ast, t_shell *shell);
t_ast		*fill_leftast(t_ast *parent);
t_ast		*fill_rightast(t_ast *parent);
t_ast		*init_ast(t_shell *shell);
void		ast_loop(t_shell *shell, t_ast *ast);
int			ast_execute(t_shell *shell, t_ast *cmd);
int	        *redirect_check(t_shell *shell);

#endif
