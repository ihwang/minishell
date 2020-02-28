/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:03:40 by tango             #+#    #+#             */
/*   Updated: 2020/02/28 22:47:14 by tango            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include "../libft/includes/libft.h"


typedef struct      s_comm
{
    char            *comm;
    char            **args;
    int             arg_nb;
    struct s_comm   *next;
}                   t_comm;

void			    parse_line(char **line, char **env);
#endif
