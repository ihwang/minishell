/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:11:58 by tango             #+#    #+#             */
/*   Updated: 2020/03/05 02:18:04 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		cmd_del(t_cmd *cmd)
{
	ft_strdel(&cmd->comm);
	cmd->arg_nb ? ft_strlst_del(&cmd->args, cmd->arg_nb + 1) : 0;
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

void        clear_com(t_cmd *c)
{
    c->arg_nb = 0;
	c->comm = NULL;
	c->args = NULL;
    c->next = NULL;
}

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
}

void        get_cmd_arg1(char *cmd, t_cmd *coms)
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
	get_cmd_arg2(coms, split);
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
    if (!ft_strcmp(coms->comm, "exit"))
		ft_exit(coms);
	else if (!ft_strcmp(coms->comm, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(coms->comm, "cd"))
		ft_cd(coms);
	else if (!ft_strcmp(coms->comm, "env"))
		ft_env();
	else if (!ft_strcmp(coms->comm, "echo"))
		ft_echo(coms);
    else if (!ft_strcmp(coms->comm, "setenv"))
        ft_setenv(coms);
    else if (!ft_strcmp(coms->comm, "unsetenv"))
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
	while (coms)
	{
		if (is_builtin(coms->comm))
			run_builtin(coms);
		else if ((path = is_in_path(coms)))
			make_child(coms, path);
	//	else if (/*The path exist*/)
	//		make_child(coms, env, NULL);
        //else
            //message handling        
        c_p = coms;
		cmd_del(c_p);
        coms = coms->next;
    }
}
