/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoipom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 14:44:47 by antoipom          #+#    #+#             */
/*   Updated: 2018/06/08 12:39:04 by antoipom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct				s_ast
{
	int						*tok;
	char					*arg;
	char					*address;
	int						split_by;
	int						depth;
	struct s_ast			*parent;
	struct s_ast			*left;
	struct s_ast			*right;
}							t_ast;

int							parser_validation(int *tk_arr);
int         				ast_evaluate(t_ast *ast);
t_ast	    				*get_ast(int **tab, char ***argv);
t_ast						*fill_leftast(t_ast *parent, int size);
t_ast						*fill_rightast(t_ast *parent, int start, int size);
t_ast						*init_ast(char ***argv);


#endif
