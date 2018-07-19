/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 13:52:25 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/07/18 18:08:28 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>

char			**fetch_from_env_o(void);
char			**fetch_from_env_a(char **all_paths);
t_list			*fetch_binaries(char **all_paths);
t_list			*add_elements(t_list *lst, char *file_bin);
t_list			*cmp_user_entry(t_list *lst, char *user_entry);
t_list			*cmp_space_entry(char *a_name);
t_list			*fetch_names(char *user_entry);
int				fetch_names_dirent(char *user_entry);
void			clean_tabs(char **t, int j);
void			send_nudes(t_list **my_phone);
void			free_lists(t_list *lst);
void			print_nudes(t_list *matches);
