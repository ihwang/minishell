/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:03:40 by tango             #+#    #+#             */
/*   Updated: 2020/03/05 02:20:05 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define KEY 1
# define VAL 0
# define PARENT 1
# define CHILD 0

#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include "../libft/includes/libft.h"

char					**g_env;

typedef struct dirent	t_dirent;

typedef struct			s_comm
{
	char				*comm;
	char            	**args;
    int             	arg_nb;
    struct s_comm   	*next;
}                   	t_cmd;

void					make_child(t_cmd *c, char *path);
int						is_eof(char *line);
void					sig_controller(int option);
char					*is_in_path(t_cmd *c);
void					ft_unsetenv(t_cmd *c);
void					ft_setenv(t_cmd *c);
void					ft_env(void);
void					ft_pwd(void);
void					ft_echo(t_cmd *c);
void					ft_exit(t_cmd *comm);
void					tild_intp(char *str);
void					dollar_intp(char *str);
void					cmd_del(t_cmd *cmd);
void					ft_cd(t_cmd *c);
void					get_prompt(void);
char					*get_env(char *name, int keyval);
void					parse_line(char **line);
#endif
