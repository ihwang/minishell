/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tango <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:11:58 by tango             #+#    #+#             */
/*   Updated: 2020/03/06 14:57:24 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
