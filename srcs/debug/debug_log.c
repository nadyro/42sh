/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsehnoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 13:18:03 by nsehnoun          #+#    #+#             */
/*   Updated: 2018/05/24 17:59:28 by nsehnoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

int     debug_level(int new_level)
{
    static int current_debug_level = DEBUG_LEVEL;
    if(new_level > 0)
        current_debug_level = new_level;
    return (current_debug_level);
}

int     get_debug_level()
{
        return (debug_level(-1));
}

int    set_debug_tty(char *tty_port, int tty_fd)
{
    static int fd = 1;

    if (tty_port != NULL)
    {
        fd = open(tty_port, O_WRONLY);
        if (isatty(fd) != -1)
        {
            ft_putendl_fd("\n------------START---------", fd);
            return (fd);
        }
        fd = 1;
    }
    else if (tty_fd > 1)
    {
        fd = tty_fd;
        if (isatty(fd) != -1)
        {
            ft_putendl_fd("\n------------START---------", fd);
            return (fd);
        }
        fd = 1;
    }
    return (fd);
}

int     get_debug_tty(void)
{
    return (set_debug_tty(NULL, 1));
}

void    debug(char *debug_log, int debug_level_requested)
{
    int tty_fd;

    tty_fd = get_debug_tty();
    if (tty_fd >= 0 && get_debug_level() >= debug_level_requested)
        ft_putstr_fd(debug_log, tty_fd);
}

void    debug_custom(void *debug_log, int type, int debug_level_requested)
{
    int tty_fd;

    tty_fd = get_debug_tty();
    if (tty_fd >= 0 && get_debug_level() >= debug_level_requested)
    {
        if (sizeof(char*) == type)
            ft_putstr_fd(debug_log, tty_fd);
        else if (sizeof(int) == type)
            ft_putnbr_fd((int)debug_log, tty_fd);

    }
}