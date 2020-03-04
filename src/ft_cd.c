/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:06:49 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/04 16:22:17 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		cd_shaping_env(char *str)
{
	char	**split;
	char	*pwd;
	int		i;

	pwd = get_env("PWD=", VAL);
	split = ft_strsplit(str, '/');
	i = -1;
	while (split[++i])
	{
		if (!ft_strcmp(split[i], ".."))
			ft_strrchr(pwd, '/') != pwd ? (*ft_strrchr(pwd, '/') = '\0') :
				(*(ft_strrchr(pwd, '/') + 1) = '\0');
		else if (!ft_strcmp(split[i], "."))
			NULL;
		else
		{
			if (!(pwd[0] == '/' && pwd[1] == '\0'))
				ft_strcat(pwd, "/");
			ft_strcat(pwd, split[i]);
		}
		chdir(pwd);
	}
	ft_strlst_del(&split, i + 1);
}

void		cd_path_finder(t_cmd *c)
{
	DIR		*dirp;
	char	*old;
	char	*pwd;

	tild_intp(c->args[0]);
	dollar_intp(c->args[0]);
	if (!(dirp = opendir(c->args[0])))
		return ; //error handling
	closedir(dirp);
	old = get_env("OLDPWD=", VAL);
	ft_bzero(old, PATH_MAX - 7);
	pwd = get_env("PWD=", VAL);
	ft_strcat(old, pwd);
	if (c->args[0][0] == '/')
	{
		ft_bzero(pwd, PATH_MAX - 4);
		ft_strcat(pwd, c->args[0]);
		chdir(pwd);
	}
	else
		cd_shaping_env(c->args[0]);
}

void        cd_no_arg(void)
{
    char    *pwd;
    char    *home;
    char    *old;

    pwd = get_env("PWD=", VAL);
    home = get_env("HOME=", VAL);
    old = get_env("OLDPWD=", VAL);
    ft_bzero(old, PATH_MAX - 7);
    ft_strcat(old, pwd);
    ft_bzero(pwd, PATH_MAX - 4);
    ft_strcat(pwd, home);
	chdir(home);
}

void        cd_exchange(void)
{
    char    *pwd;
    char    *old;
    char    *temp;

    temp = (char*)malloc(PATH_MAX);
    ft_bzero(temp, PATH_MAX);
    pwd = get_env("PWD=", VAL);
	ft_strcat(temp, pwd);
    old = get_env("OLDPWD=", VAL);
    ft_bzero(pwd, PATH_MAX - 4);
    ft_strcat(pwd, old);
    ft_bzero(old, PATH_MAX - 7);
	ft_strcat(old, temp);
	ft_strdel(&temp);
	chdir(pwd);
}

void        ft_cd(t_cmd *c)
{
    if (!c->arg_nb)
        cd_no_arg();
    else if (!ft_strcmp(c->args[0], "-"))
        cd_exchange();
	else
		cd_path_finder(c);
}
