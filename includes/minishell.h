/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:03:40 by tango             #+#    #+#             */
/*   Updated: 2020/03/03 01:00:10 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define KEY 1
# define VAL 0

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
}                   t_cmd;

void				ft_setenv(t_cmd *c, char ***env);
void				ft_env(char ***env);
void				ft_pwd(char ***env);
void				ft_echo(t_cmd *c, char ***env);
void				ft_exit(t_cmd *comm, char ***env);
void				tild_intp(char *str, char ***env);
void				dollar_intp(char *str, char ***env);
void				cmd_del(t_cmd *cmd);
void				ft_cd(t_cmd *c, char ***env);
char				*get_env(char ***env, char *name, int keyval);
void			    parse_line(char **line, char ***env);
#endif
