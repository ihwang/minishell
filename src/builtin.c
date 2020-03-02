/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:11:58 by tango             #+#    #+#             */
/*   Updated: 2020/03/02 18:38:35 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		cmd_del(t_cmd *cmd)
{
	ft_strdel(&cmd->comm);
	cmd->arg_nb ? ft_strlst_del(&cmd->args, cmd->arg_nb + 1) : 0;
	free(cmd);
}

char        *get_env(char ***env, char *name)
{
    int     i;

    i = -1;
    while (env[0][++i])
        if (ft_strstr(env[0][i], name) && name[0] == env[0][i][0])
            return (ft_strstr_e(env[0][i], name));
    return (NULL);
}

void        clear_com(t_cmd *c)
{
    c->arg_nb = 0;
	c->comm = NULL;
	c->args = NULL;
    c->next = NULL;
}

void        get_cmd_arg(char *cmd, t_cmd *coms)
{
    char    **split;
    int     i;

    i = -1;
    split = ft_strsplit(cmd, ' ');
    while (split[++i])
        NULL;
    coms->comm = (char*)malloc(PATH_MAX);
    ft_bzero(coms->comm, PATH_MAX);
    ft_strcpy(coms->comm, split[0]);
    coms->arg_nb = i - 1;
	if (coms->arg_nb)
	{
		coms->args = (char**)malloc(sizeof(char*) * (coms->arg_nb + 1));
		i = -1;
		while (split[++i + 1])
		{
			coms->args[i] = (char*)malloc(sizeof(char) * PATH_MAX);
			ft_bzero(coms->args[i], PATH_MAX);
			ft_strcat(coms->args[i], split[i + 1]);
		}
		coms->args[i] = NULL;
	}
    coms->next = NULL;
    ft_strlst_del(&split, coms->arg_nb + 2);
}

t_cmd		*get_coms(char **line)
{
    char    **cmd_lst;
    int     i;
    t_cmd  *coms;
    t_cmd  *c_t;
    t_cmd  *c_p;

    cmd_lst = ft_strsplit(*line, ';');
    ft_strdel(line);
    coms = (t_cmd*)malloc(sizeof(t_cmd));
	clear_com(coms);
    c_p = coms;
    get_cmd_arg(cmd_lst[0], c_p);
    i = 0;
    while (cmd_lst[++i])
    {
        c_t = (t_cmd*)malloc(sizeof(t_cmd));
		clear_com(c_t);
        get_cmd_arg(cmd_lst[i], c_t);
        c_p->next = c_t;
        c_p = c_p->next;
    }
    ft_strlst_del(&cmd_lst, i + 1);
    return (coms);
}

int         is_builtin(char *comm)
{
    if (!ft_strcmp(comm, "exit") || !ft_strcmp(comm, "echo")
        || !ft_strcmp(comm, "cd") || !ft_strcmp(comm, "env")
        || !ft_strcmp(comm, "setenv") || !ft_strcmp(comm, "unsetenv")
        || !ft_strcmp(comm, "pwd"))
        return (1);
    return (0);
}

void        run_builtin(t_cmd *coms, char ***env)
{
    if (!ft_strcmp(coms->comm, "exit"))
		ft_exit(coms, env);
	else if (!ft_strcmp(coms->comm, "pwd"))
		ft_pwd(env);
	else if (!ft_strcmp(coms->comm, "cd"))
		ft_cd(coms, env);
	else if (!ft_strcmp(coms->comm, "env"))
		ft_env(env);
	else if (!ft_strcmp(coms->comm, "echo"))
		ft_echo(coms, env);
    else if (!ft_strcmp(coms->comm, "setenv"))
        ft_setenv(coms, env);
	/*
    else if (!ft_strcmp(coms[i].comm, "unsetenv"))
        ft_unsetenv();
    */
}

void		parse_line(char **line, char ***env)
{
    t_cmd  *coms;
    t_cmd  *c_p;
    int     i;

    if (line[0][0] == '\0')
        return (ft_strdel(line));
    coms = get_coms(line);
    i = -1;
    while (coms)
    {
        if (is_builtin(coms->comm))
            run_builtin(coms, env);
       /* else if (is_in_PATH)
        {
            //forking and execve
        }
        else
        {
            //message handling        
        }*/
        c_p = coms;
		cmd_del(c_p);
        coms = coms->next;
    }
}
