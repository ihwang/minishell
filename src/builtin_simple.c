/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 02:33:55 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/02 19:30:53 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void        ft_pwd(char ***env)
{
    char    *pwd;

    pwd = get_env(env, "PWD=");
    ft_putstr(pwd);
    ft_putstr("\n");
}

void        ft_exit(t_cmd *coms, char ***env)
{
    t_cmd  *c_p;
    int     i;

    while (coms)
    {
        c_p = coms;
        coms = coms->next;
        cmd_del(c_p);
    }
    i = -1;
    while (env[0][++i])
        ft_strdel(&env[0][i]);
    ft_strdel(&env[0][i]);
    free(env[0]);
	while (1)
		NULL;
    exit(0);
}

void		ft_echo(t_cmd *c, char ***env)
{
	int		i;

	i = -1;
	while (++i < c->arg_nb)
	{
		tild_intp(c->args[i], env);
		dollar_intp(c->args[i], env);
		ft_putstr(c->args[i]);
		if (i + 1 != c->arg_nb && ft_strcmp(c->args[i], ""))
			ft_putstr(" ");
	}
	ft_putchar('\n');
}

void		add_env(char *str, char ***env)
{
	int		i;
	char	**temp;

	i = -1;
	while (env[0][++i])
		NULL;
	temp = (char**)malloc(sizeof(char*) * (i + 2));
	i = -1;
	while (env[0][++i])
	{
		temp[i] = (char*)malloc(sizeof(char) * PATH_MAX);
		ft_strcpy(temp[i], env[0][i]);
	}
	temp[i] = (char*)malloc(sizeof(char) * PATH_MAX);
	ft_strcpy(temp[i], str);
	temp[i + 1] = NULL;
	ft_strlst_del(env, i);
	env[0] = temp;
	//////HERE
	//and
	//NEED TO FINISH SETENV
}

void		ft_setenv(t_cmd *c, char ***env)
{
	int		i;
	int		j;
	char	**split;
	char	*var;

	i = -1;
	while (++i < c->arg_nb)
	{
		tild_intp(c->args[i], env);
		dollar_intp(c->args[i], env);
		j = -1;
		while (ft_isalnum(c->args[i][++j]))
			NULL;
		if (c->args[i][j] =='\0')
			return ;
		else if (c->args[i][j] != '=' || j == 0)
			return (ft_putstr("errro"));
		split = ft_strsplit(c->args[i], '=');
		if ((var = get_env(env, split[0])))
		{
			var++;
			j = 0;
			var[0] = '\0';
			while(split[++j])
				ft_strcat(var, split[j]);
		}
		else
		{
			add_env(c->args[i], env);
		}
	}
}
