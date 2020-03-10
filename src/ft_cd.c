/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:06:49 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/10 17:18:19 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cd_shaping_env(char *str)
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

static void	cd_path_finder(t_cmd *c)
{
	char	*old;
	char	*pwd;
	char	temp_pwd[PATH_MAX];

	if (!there_is_d(c))
		return ;
	pwd = get_env("PWD=", VAL);
	if ((old = get_env("OLDPWD=", VAL)))
	{
		ft_bzero(old, PATH_MAX - 7);
		ft_strcat(old, pwd);
	}
	else
		make_old();
	if (c->av[1][0] == '/')
	{
		ft_strcpy(temp_pwd, c->av[1]);
		chdir(temp_pwd);
		getcwd(temp_pwd, PATH_MAX);
		ft_bzero(pwd, PATH_MAX - 4);
		ft_strcat(pwd, temp_pwd);
	}
	else
		cd_shaping_env(c->av[1]);
}

static void	cd_no_arg(void)
{
	char	*pwd;
	char	*home;
	char	*old;

	pwd = get_env("PWD=", VAL);
	home = get_env("HOME=", VAL);

	if ((old = get_env("OLDPWD=", VAL)))
	{
		ft_bzero(old, PATH_MAX - 7);
		ft_strcat(old, pwd);
	}
	else
		make_old();
	ft_bzero(pwd, PATH_MAX - 4);
	ft_strcat(pwd, home);
	chdir(home);
}

static void	cd_exchange(void)
{
	char	*pwd;
	char	*old;
	char	*temp;

	temp = (char*)malloc(PATH_MAX);
	ft_bzero(temp, PATH_MAX);
	pwd = get_env("PWD=", VAL);
	ft_strcat(temp, pwd);
	if ((old = get_env("OLDPWD=", VAL)))
	{
		ft_bzero(pwd, PATH_MAX - 4);
		ft_strcat(pwd, old);
		ft_bzero(old, PATH_MAX - 7);
		ft_strcat(old, temp);
	}
	else
		ft_putstr("cd: OLDPWD not set\n");
	ft_strdel(&temp);
	chdir(pwd);
}

void		ft_cd(t_cmd *c)
{
	if (c->ac == 1)
		cd_no_arg();
	else if (!ft_strcmp(c->av[1], "-"))
		cd_exchange();
	else
		cd_path_finder(c);
}
