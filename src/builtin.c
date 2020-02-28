/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:11:58 by tango             #+#    #+#             */
/*   Updated: 2020/02/29 01:25:43 by tango            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        clear_com(t_comm *c)
{
    c->arg_nb = 0;
//  c->comm = NULL;
//  c->args = NULL;
    c->next = NULL;
}

void        get_cmd_arg(char *cmd, t_comm *coms)
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
    coms->args = &split[1];
    coms->arg_nb = i - 1;
    coms->next = NULL;
    ft_strlst_del(&split, i + 1);
}

t_comm		*get_coms(char **line)
{
    char    **cmd_lst;
    int     i;
    t_comm  *coms;
    t_comm  *c_t;
    t_comm  *c_p;

    cmd_lst = ft_strsplit(*line, ';');
    ft_strdel(line);
    coms = (t_comm*)malloc(sizeof(t_comm));
  //  clear_com(coms);
    c_p = coms;
    get_cmd_arg(cmd_lst[0], c_p);
    i = 0;
    while (cmd_lst[++i])
    {
        c_t = (t_comm*)malloc(sizeof(t_comm));
  //      clear_com(c_t);
        get_cmd_arg(cmd_lst[i], c_t);
        c_p->next = c_t;
        c_p = c_p->next;
    }
    ft_strlst_del(&cmd_lst, i + 1);
    return (coms);
}

void        ft_exit(t_comm *coms)
{
    t_comm  *c_p;
    int     j;

    c_p = coms;
    while (c_p)
    {
        ft_strdel(&(c_p->comm));
        j = -1;
        while (++j < c_p->arg_nb)
            free(c_p->args[j]);
        c_p->arg_nb ? free(c_p->args) : 0;
        free(c_p);
        c_p = c_p->next;
    }
    exit(0);
}

int         is_builtin(char *comm)
{
    if (!ft_strcmp(comm, "exit") || !ft_strcmp(comm, "echo")
        || !ft_strcmp(comm, "cd") || !ft_strcmp(comm, "env")
        || !ft_strcmp(comm, "setenv") || !ft_strcmp(comm, "unsetenv"))
        return (1);
    return (0);
}

void        run_builtin(t_comm *coms, char **env)
{
    env = NULL;
    if (!ft_strcmp(coms->comm, "exit"))
        ft_exit(coms);
  /*  else if (!ft_strcmp(coms[i].comm, "echo"))
        ft_echo(();
    else if (!ft_strcmp(coms[i].comm, "cd"))
        ft_cd();
    else if (!ft_strcmp(coms[i].comm, "env"))
        ft_env();
    else if (!ft_strcmp(coms[i].comm, "setenv"))
        ft_setenv();
    else if (!ft_strcmp(coms[i].comm, "unsetenv"))
        ft_unsetenv();
    */
}

void		parse_line(char **line, char **env)
{
    t_comm  *coms;
    t_comm  *c_p;
    int     i;

    if (line[0][0] == '\0')
        return (ft_strdel(line));
    coms = get_coms(line);
    c_p = coms;
    i = -1;
    while (c_p)
    {
        if (is_builtin(c_p->comm))
            run_builtin(c_p, env);
       /* else if (is_in_PATH)
        {
            //forking and execve
        }
        else
        {
            //message handling        
        }*/
        c_p = c_p->next;
    }
}
