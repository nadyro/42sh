/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 13:12:46 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/28 19:22:37 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

#ifndef DEBUG_LEVEL
# define DEBUG_LEVEL 0
#endif

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>

enum {DBSTR, DBINT, DBTYPE_COUNT};

int     debug_level(int new_level);
int     get_debug_level();
int     set_debug_tty(char *tty_port, int tty_fd);
int     get_debug_tty(void);
void    debug(char *debug_log, int debug_level_requested);
void    debug_custom(void *debug_log, int type, int debug_level_requested);

#endif