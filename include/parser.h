/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:27:44 by arohani           #+#    #+#             */
/*   Updated: 2018/07/25 17:45:15 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <builtins.h>

typedef struct	s_redirs
{
	int						beg;
	int						end;
	int						next_re;
	int 					new_fd;
	int 					ionum; // ft_atoi(str) with str = ft_strndup(shell->line + shell->tok[beg + 1], shell->tok[beg + 2]);
	int						handled;
	struct s_redirs			*prev;
	struct s_redirs			*next;
}				t_redirs;

typedef struct	s_ast
{
	int 					beg;	//relevant start token in token table for ast node
	int 					end;	//relevant end token in token table for ast node
	int 					split;	//relevant position where split operator token was found in token table
	int						cmd_ret;
	struct s_ast			*parent;
	struct s_ast			*left;
	t_redirs				*redirs;
	struct s_ast			*right;
}				t_ast;

int			parser_validation(int *tk_arr, char *ine);
void		create_arg_table(t_shell *shell, int beg, int end);
int 		get_tk_end_pos(t_shell *shell);
t_ast	    *get_ast(t_shell *shell);
int         ast_evaluate(t_ast *ast, t_shell *shell);
t_ast		*fill_leftast(t_ast *parent);
t_ast		*fill_rightast(t_ast *parent);
t_ast		*init_ast(t_shell *shell);
void		ast_loop(t_shell *shell, t_ast *ast);
int			ast_execute(t_shell *shell, t_ast *cmd);
int	        *redirect_check(t_shell *shell);
int			is_redirect(t_shell *shell, t_ast *ast, int beg, int end);
int			is_fd(char *str, int len);
void		fill_redirs(t_shell *shell, t_ast *ast, int beg, int redir);
void 		implement_redirs(t_shell *shell, t_ast *cmd);
void		restore_std_fds(t_shell *shell, t_redirs *rd);

#endif
