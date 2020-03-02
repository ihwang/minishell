/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 00:41:54 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/03 01:06:40 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		add_env(char *arg, char ***env)
{
	int		i;
	char	**temp;

	i = -1;
	while (env[0][++i])
		NULL;
	temp = (char**)malloc(sizeof(char*) * (i + 2));
	i = -1;
	while (env[0][++i])
		temp[i] = env[0][i];
	temp[i] = (char*)malloc(sizeof(char) * PATH_MAX);
	ft_strcpy(temp[i], arg);
	temp[i + 1] = NULL;
	free(env[0]);
	env[0] = temp;
}

void		ft_setenv_sub(char *arg, char ***env)
{
	char	**split;
	char	*var;
	int		j;

	split = ft_strsplit(arg, '=');
	if ((var = get_env(env, split[0], VAL)))
	{
		var++;
		j = 0;
		var[0] = '\0';
		while (split[++j])
			ft_strcat(var, split[j]);
	}
	else
		add_env(arg, env);
	j = -1;
	while (split[++j])
		NULL;
	ft_strlst_del(&split, j + 1);
}

void		ft_setenv(t_cmd *c, char ***env)
{
	int		i;
	int		j;
	//char	**split;
	//char	*var;

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
			return (ft_putstr("errro\n"));
		else
			ft_setenv_sub(c->args[i], env);
	}
}
/*
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
}*/
