/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohani <arohani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 16:02:30 by arohani           #+#    #+#             */
/*   Updated: 2018/08/16 19:37:27 by arohani          ###   ########.fr       */
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
	int						ionum;
	struct s_redirs			*prev;
	struct s_redirs			*next;
}				t_redirs;

typedef struct	s_ast
{
	int						beg;
	int						end;
	int						split;
	int						cmd_ret;
	int						hfd[2];
	int						hd_check;
	struct s_ast			*parent;
	struct s_ast			*left;
	t_redirs				*redirs;
	struct s_ast			*right;
}				t_ast;

#endif
