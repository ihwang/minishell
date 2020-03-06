/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:03:40 by tango             #+#    #+#             */
/*   Updated: 2020/03/06 15:17:02 by ihwang           ###   ########.fr       */
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

typedef struct			s_cmd
{
	int					ac;
	char				**av;
	struct s_cmd		*next;
}						t_cmd;

void					print_no_cmd(char *str);
void					print_unsetenv(char *str);
int						there_is_e(t_cmd *c);
int						there_is_d(t_cmd *c);
void					make_child_not_env(t_cmd *c);
void					make_child_env(t_cmd *c, char *path);
int						is_eof(char *line);
char					*is_in_path(t_cmd *c);
void					ft_pwd(void);
void					ft_echo(t_cmd *c);
void					ft_exit(t_cmd *comm);
void					ft_env(void);
void					ft_cd(t_cmd *c);
void					ft_unsetenv(t_cmd *c);
void					ft_setenv(t_cmd *c);
void					sig_controller(int option);
void					cmd_del(t_cmd *c);
char					*get_env(char *name, int keyval);
void					apply_t_d(t_cmd *c);
void					execute_cmd(t_cmd *c, char *path);
void					parse_line(char **line);
void					get_prompt(void);
#endif
