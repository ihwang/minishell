/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:11:58 by tango             #+#    #+#             */
/*   Updated: 2020/02/29 03:55:04 by tango            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void        com_del(t_comm *c)
{
    ft_strdel(&c->comm);
    c->arg_nb ? ft_strlst_del(&c->args, c->arg_nb) : 0;
    free(c);
}

char        *get_env(char ***env, char *name)
{
    int     i;

    i = -1;
    while (env[0][++i])
        if (ft_strstr(env[0][i], name) && name[0] == env[0][i][0])
            return (env[0][i]);
    return (NULL);
}

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

void        ft_exit(t_comm *coms, char ***env)
{
    t_comm  *c_p;
    int     i;

    while (coms)
    {
        c_p = coms;
        coms = coms->next;
        com_del(c_p);
    }
    i = -1;
    while (env[0][++i])
        ft_strdel(&env[0][i]);
    ft_strdel(&env[0][i]);
    free(env[0]);
    exit(0);
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

void        ft_pwd(char ***env)
{
    char    *pwd;

    pwd = get_env(env, "PWD=");
    pwd = ft_strstr_e(pwd, "PWD=");
    ft_putstr(pwd);
    ft_putstr("\n");
}



void        cd_no_arg(char ***env)
{
    char    *pwd;
    char    *home;
    char    *old;

    pwd = get_env(env, "PWD=");
    pwd = ft_strstr_e(pwd, "PWD=");
    home = get_env(env, "HOME=");
    home = ft_strstr_e(home, "HOME=");
    old = get_env(env, "OLDPWD=");
    old = ft_strstr_e(old, "OLDPWD=");
    ft_bzero(old, PATH_MAX - 7);
    ft_strcat(old, pwd);
    ft_bzero(pwd, PATH_MAX - 4);
    ft_strcat(pwd, home);
}

void        cd_exchange(char ***env)
{
    char    *pwd;
    char    *old;
    char    *temp;

    temp = (char*)malloc(PATH_MAX);
    ft_bzero(temp, PATH_MAX);

    pwd = get_env(env, "PWD=");
    pwd = ft_strstr_e(pwd, "PWD=");

    old = get_env(env, "OLDPWD=");
    old = ft_strstr_e(pwd, "OLDPWD=");

    ft_bzero(pwd, PATH_MAX - 4);
    ft_strcat(pwd, old);
    ft_bzero(
///////////////////working on this function!!!//////////////////
}

void        ft_cd(t_comm *c, char ***env)
{
    //int     i;
    //char    *pwd;

    if (!c->arg_nb)
        cd_no_arg(env);
    else if (!ft_strcmp(c->args[0], '-'))
        cd_exchange(env);

}

void        ft_env(char ***env)
{
    int     i;

    i = -1;
    while (env[0][++i])
    {
        ft_putstr(env[0][i]);
        ft_putstr("\n");
    }
}

void        run_builtin(t_comm *coms, char ***env)
{
    !ft_strcmp(coms->comm, "exit") ? ft_exit(coms, env) : 0;
    !ft_strcmp(coms->comm, "pwd") ? ft_pwd(env) : 0;
    !ft_strcmp(coms->comm, "cd") ? ft_cd(coms, env) : 0;
    !ft_strcmp(coms->comm, "env") ? ft_env(env) : 0;
        //ft_exit(coms);
   // if (!ft_strcmp(coms->comm, "pwd"))
     //   ft_pwd();
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

void		parse_line(char **line, char ***env)
{
    t_comm  *coms;
    t_comm  *c_p;
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
        com_del(c_p);
        coms = coms->next;
    }
}
