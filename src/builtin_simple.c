/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 02:33:55 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/03 01:43:49 by ihwang           ###   ########.fr       */
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

    pwd = get_env(env, "PWD=", VAL);
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
//	while (1)
//		NULL;
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

void		ft_unsetenv(t_cmd *c, char ***env)
{
	int		i;
	int		j;
	int		nb;
	char	*var;

	i = -1;
	while (++i < c->arg_nb)
	{
		j = -1;
		while (ft_isalnum(c->args[i][++j]))
			NULL;
		if (c->args[i][j] != '\0')
			return (ft_putstr("error\n"));
		ft_strcat(c->args[i], "=");
		j = -1;
		while (
//////////////////////////////////////////////
				//here
// modified get_env and added MACROS for ft_unsetenv
// These need to be tested.

		nb = -1;
		while (env[0][++nb])
			NULL;

