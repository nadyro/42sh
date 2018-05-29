/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lining.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:12:46 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/29 23:26:56 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINING_H
# define LINING_H

# include "../libft/libft.h"
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include "debug.h"

# define BUFFER 1024
# define COLSTART 11
# define K_SLEFT 74982532143899
# define K_SRIGHT 73883020516123
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define BCYAN "\x1B[96m"
# define NORMAL "\x1b[0m"
# define MALLOC NULL

struct					s_cursor_data
{
	int		o_pos_x;
	int		o_pos_y;
	int		pos_x;
	int		pos_y;
	int		x;
	int		cp_state;
	int		cp_start;
	int		cp_end;
	int		cp_front;
	int		cp_active;
	int		avg_cp;
	int		col;
	int		row;
};
struct					s_win
{
	int		win_col;
	int		win_row;
};
struct					s_line_data
{
	void					*content;
	void					*old_content;
	char					*buff;
	char					*buffer;
	char					*tmp;
	int						current_size;
	int						length;
	int						nb_resize;
	int						h_elem;
	int						nb_lines;
	int						last_line;
	int						c;
	int						d;
	t_list					*history;
	struct s_cursor_data	*cd;
	struct s_win			*sw;
};
int						fprint_char(int c);
void					get_infoterm(void);
struct s_line_data		*init_linedata(void);
void					clean_linedata(struct s_line_data *ld);
struct s_cursor_data	*init_cursordata(void);
void					manage_movement(char *t, struct s_line_data *ld, int *index);
void					manage_validation(struct s_line_data *ld, t_list **history);
void					reallocate_mem_line(struct s_line_data *ld);
void					print_line_data(struct s_line_data *ld, t_list *history);
void					move_left(struct s_line_data *ld);
void					move_right(struct s_line_data *ld);
void					move_up(struct s_line_data *ld);
void					move_down(struct s_line_data *ld);
void					update_linedata(char *t, struct s_line_data *ld);
void					cursor_pos(struct s_line_data *ld);
void					ft_putscolors(char *str, char *color);
void					write_change(struct s_line_data *ld, int is_rewrite);
int						manage_buffer(struct s_line_data *ld, char *t, int *i);
void					ft_exit(int nb);
struct s_win			*init_windata(void);
void					manage_controls(char t, struct s_line_data *ld, int *i);
void					manage_cp_pst(char *t, struct s_line_data *ld, char *tmp_buffer);
void					manage_key_insertion(char *t, struct s_line_data *ld, char *tmp_buffer);
void					manage_deletion(struct s_line_data *ld);
void					write_fromstart(struct s_line_data *ld, int is_todel);
int						dispatch_tasks(struct s_line_data *ld, char *t, int *index);
void					skip_word_left(struct s_line_data *ld);
void					skip_word_right(struct s_line_data *ld);
void					gt_start_end_del(struct s_line_data *ld, char t, int *index);
void					cp_cut(struct s_line_data *ld, int *index, char t);
void					cp_copy_select_cp(struct s_line_data *ld, char t);
void					cp_paste(struct s_line_data *ld, char t, int *index);
void					cp_end_select_cp(struct s_line_data *ld, char t);
void					print_endslct(struct s_line_data *ld);
t_list					*write_history(struct s_line_data *ld, t_list **history);
void					write_history_file(t_list *history);
void					browse_history_up(struct s_line_data *ld, int *index);
void					browse_history_down(struct s_line_data *ld, int *index);
int						check_line_length(struct s_line_data *ld);
#endif
