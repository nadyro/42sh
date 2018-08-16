/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:27:44 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 19:35:08 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define T2S_BLOCK 0xFF
# define T2S_CUR 0
# define T2S_OLD 1
# include "builtins.h"
# include "shell_structs.h"

typedef struct	s_t2s
{
	char	*buffer[2];
	int		i[2];
	int		m[2];
	int		cursor[2];
	int		stat[2];
}				t_t2s;

char			*token2str(int *token, char *str, char **env);
int				parser_validation(int *tk_arr, char *ine);
void			ast_loop_semi(t_ast *head, t_shell *shell, int i);
void			ast_loop_and_or(t_ast *head, t_shell *shell, int i);
void			ast_loop_pipe(t_ast *head, t_shell *shell, int i);
void			create_arg_table(t_shell *shell, int beg, int end);
int				get_tk_end_pos(t_shell *shell);
t_ast			*get_ast(t_shell *shell);
int				ast_evaluate(t_ast *ast, t_shell *shell);
t_ast			*fill_leftast(t_ast *parent);
t_ast			*fill_rightast(t_ast *parent);
t_ast			*init_ast(t_shell *shell);
int				ast_execute(t_shell *shell, t_ast *cmd, int env_ex);
int				*redirect_check(t_shell *shell);
int				is_redirect(t_shell *shell, t_ast *ast, int beg, int end);
int				is_fd(char *str, int len);
void			fill_redirs(t_shell *shell, t_ast *ast, int beg, int redir);
void			implement_redirs(t_shell *shell, t_ast *cmd);
void			restore_std_fds(t_shell *shell, t_ast *cmd, t_redirs *rd);
int				evaluate_pipe_node(t_shell *shell, t_ast *cmd);
void			implement_great(t_shell *shell, t_redirs *node, int fd);
void			implement_dgreat(t_shell *shell, t_redirs *node, int fd);
void			implement_greatand(t_shell *shell, t_redirs *node, int fd);
void			implement_less(t_shell *shell, t_redirs *node, int fd);
void			implement_lessand(t_shell *shell, t_redirs *node, int fd);
void			implement_heredoc(t_ast *cmd, int id);
int				last_heredoc_id(t_shell *shell, t_redirs *node);
void			redir_error(t_shell *shell, char *filename, int new_fd);
void			shell_args_from_redirs(t_shell *shell, t_ast *cmd);
void			free_ast(t_ast *head);
void			free_redirs(t_redirs *list);
int				t2s_init(t_t2s **t2s);
int				t2s_realloc(t_t2s *t2s, char buffer);
int				t2s_init_b(t_t2s *t2s);
void			main_loop(char *line, t_shell shell);

#endif
