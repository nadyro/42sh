/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 16:02:30 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 16:05:07 by arohani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_STRUCTS_H
# define SHELL_STRUCTS_H

typedef struct	s_redirs
{
	int						beg;
	int						end;
	int						next_re;
	int						new_fd;
	int 					ionum; // ft_atoi(str) with str = ft_strndup(shell->line + shell->tok[beg + 1], shell->tok[beg + 2]);
	struct s_redirs			*prev;
	struct s_redirs			*next;
}				t_redirs;

typedef struct	s_ast
{
	int 					beg;	//relevant start token in token table for ast node
	int 					end;	//relevant end token in token table for ast node
	int 					split;	//relevant position where split operator token was found in token table
	int						cmd_ret;
	int						hfd[2];
	int						hd_check;
	struct s_ast			*parent;
	struct s_ast			*left;
	t_redirs				*redirs;
	struct s_ast			*right;
}				t_ast;

#endif