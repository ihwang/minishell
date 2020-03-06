/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:11:58 by tango             #+#    #+#             */
/*   Updated: 2020/03/06 14:37:40 by ihwang           ###   ########.fr       */
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
	c_p = coms;
	i = 0;
	while (cmd_lst[++i])
	{
		c_t = (t_cmd*)malloc(sizeof(t_cmd));
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

void			execute_cmd(t_cmd *c, char *path)
{
	if (is_builtin(c->av[0]))
		run_builtin(c);
	else if ((path = is_in_path(c)))
		make_child_env(c, path);
	else if (there_is_e(c))
		make_child_not_env(c);
	else
		print_no_cmd(c->av[0]);
}

void			apply_t_d(t_cmd *c)
{
	int			i;

	i = -1;
	while (++i < c->ac)
	{
		tild_intp(c->av[i]);
		dollar_intp(c->av[i]);
	}
}

void			parse_line(char **line)
{
	t_cmd		*coms;
	t_cmd		*c_p;
	char		*path;
	char		*trim;

	path = NULL;
	trim = ft_strtrim(*line);
	ft_strdel(line);
	if (trim[0] == '\0')
		return (ft_strdel(&trim));
	coms = get_coms(&trim);
	c_p = coms;
	while (c_p)
	{
		apply_t_d(c_p);
		execute_cmd(c_p, path);
		coms = c_p;
		c_p = c_p->next;
		cmd_del(coms);
	}
}
