/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:11:58 by tango             #+#    #+#             */
/*   Updated: 2020/03/05 15:00:17 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		cmd_del(t_cmd *cmd)
{
	ft_strlst_del(&(cmd->av), cmd->ac + 1);
	free(cmd);
}

char        *get_env(char *name, int keyval)
{
    int     i;
	char	*ret;

    i = -1;
	while (g_env[++i])
	{
		if (keyval == VAL)
		{
			if (ft_strstr(g_env[i], name) && name[0] == g_env[i][0])
				return (ft_strstr_e(g_env[i], name));
		}
		else
		{
			if ((ret = ft_strstr(g_env[i], name)) && name[0] == g_env[i][0])
					return (ret);
		}
	}
    return (NULL);
}

/*void        clear_com(t_cmd *c)
{
    c->arg_nb = 0;
	c->comm = NULL;
	c->args = NULL;
    c->next = NULL;
}*/

void		clear_cmd(t_cmd *c)
{
	c->ac = 0;
	c->av = NULL;
	c->next = NULL;
}
/*
void		get_cmd_arg2(t_cmd *coms, char **split)
{
	int		i;

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
}*/

/*
void        get_cmd_arg1(char *cmd, t_cmd *coms)
{
    char    **split;
    int     i;

    i = -1;
    split = ft_strsplit(cmd, ' ');
    while (split[++i])
        NULL;
    coms->comm = (char*)malloc(PATH_MAX);
    ft_strcpy(coms->comm, split[0]);
    coms->arg_nb = i - 1;
	get_cmd_arg2(coms, split);
    coms->next = NULL;
    ft_strlst_del(&split, coms->arg_nb + 2);
}
*/

void		get_cmd_arg(char *cmd, t_cmd *c)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_strsplit(cmd, ' ');
	while (split[++i])
		NULL;
	c->ac = i;
	c->av = (char**)malloc(sizeof(char*) * (i + 1));
	i = -1;
	while (++i < c->ac)
	{
		c->av[i] = (char*)malloc(PATH_MAX);
		ft_strcpy(c->av[i], split[i]);
	}
	c->av[i] = NULL;
	c->next = NULL;
	ft_strlst_del(&split, i + 1);
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
	get_cmd_arg(cmd_lst[0], coms);
//	clear_com(coms);
	c_p = coms;
	i = 0;
    while (cmd_lst[++i])
    {
        c_t = (t_cmd*)malloc(sizeof(t_cmd));
//		clear_com(c_t);
        get_cmd_arg(cmd_lst[i], c_t);
        c_p->next = c_t;
        c_p = c_p->next;
    }
    ft_strlst_del(&cmd_lst, i + 1);
    return (coms);
}

/*
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
    get_cmd_arg1(cmd_lst[0], c_p);
    i = 0;
    while (cmd_lst[++i])
    {
        c_t = (t_cmd*)malloc(sizeof(t_cmd));
		clear_com(c_t);
        get_cmd_arg1(cmd_lst[i], c_t);
        c_p->next = c_t;
        c_p = c_p->next;
    }
    ft_strlst_del(&cmd_lst, i + 1);
    return (coms);
}
*/

int         is_builtin(char *comm)
{
    if (!ft_strcmp(comm, "exit") || !ft_strcmp(comm, "echo")
        || !ft_strcmp(comm, "cd") || !ft_strcmp(comm, "env")
        || !ft_strcmp(comm, "setenv") || !ft_strcmp(comm, "unsetenv")
        || !ft_strcmp(comm, "pwd"))
        return (1);
    return (0);
}

void        run_builtin(t_cmd *coms)
{
    if (!ft_strcmp(coms->av[0], "exit"))
		ft_exit(coms);
	else if (!ft_strcmp(coms->av[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(coms->av[0], "cd"))
		ft_cd(coms);
	else if (!ft_strcmp(coms->av[0], "env"))
		ft_env();
	else if (!ft_strcmp(coms->av[0], "echo"))
		ft_echo(coms);
    else if (!ft_strcmp(coms->av[0], "setenv"))
        ft_setenv(coms);
    else if (!ft_strcmp(coms->av[0], "unsetenv"))
        ft_unsetenv(coms);
}

void			parse_line(char **line)
{
	t_cmd		*coms;
	t_cmd		*c_p;
	char		*path;
	char		*trim;

	trim = ft_strtrim(*line);
	ft_strdel(line);
    if (trim[0] == '\0')
        return (ft_strdel(&trim));
	coms = get_coms(&trim);
	c_p = coms;
	while (c_p)
	{
		if (is_builtin(c_p->av[0]))
			run_builtin(c_p);
		else if ((path = is_in_path(c_p)))
			make_child(c_p, path);
	//	else if (/*The path exist*/)
	//		make_child(coms, env, NULL);
        //else
            //message handling        
		coms = c_p;
        c_p = c_p->next;
		cmd_del(coms);
    }
}
