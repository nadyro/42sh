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
	int						*tok;
	int						cmd_ret;
	char					*address;
	char					*arg;
	int						split_by;
	int						depth;
	struct s_ast			*parent;
	struct s_ast			*left;
	struct s_ast			*right;
}				t_ast;

int			parser_validation(int *tk_arr, char *ine);
t_ast	    *get_ast(char *argv);
int         ast_evaluate(t_ast *ast, t_shell *shell);
t_ast		*fill_leftast(t_ast *parent, int size);
t_ast		*fill_rightast(t_ast *parent, int start, int size);
t_ast		*init_ast(char *argv);
void		ast_loop(t_shell *shell, t_ast *ast);
int			ast_execute(t_shell *shell, t_ast *cmd);
int	        *redirect_check(t_shell *shell);

#endif
