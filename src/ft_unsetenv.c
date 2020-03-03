/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:41:57 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/03 18:42:26 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		del_replace(char ***env, char *str)
{
	int		nb;
	int		i;
	int		j;
	char	**temp;

	nb = -1;
	while (env[0][++nb])
		NULL;
	temp = (char**)malloc(sizeof(char*) * nb - 1);
	i = -1;
	j = 0;
	while (++i < nb - 1)
	{
		if (!ft_strstr(env[0][i], str))
		{
			temp[j] = (char*)malloc(PATH_MAX);
			ft_strcpy(temp[j++], env[0][i]);
		}
	}
	ft_strlst_del(env, nb + 1);
	env[0] = temp;
}

int			is_env(char ***env, char *str)
{
	int		i;
	char	*dot;

	i = -1;
	while (env[0][++i])
	{
		dot = ft_strchr(env[0][i], '=');
		*dot = '\0';
		if (!ft_strcmp(env[0][i], str))
		{
			*dot = '=';
			return (1);
		}
		*dot = '=';
	}
	return (0);
}

void		ft_unsetenv(t_cmd *c, char ***env)
{
	int		i;
	int		j;

	i = -1;
	while (++i < c->arg_nb)
	{
		tild_intp(c->args[i], env);
		dollar_intp(c->args[i], env);
		j = -1;
		while (ft_isalnum(c->args[i][++j]))
			NULL;
		if (c->args[i][j] != '\0')
			return (ft_putstr("error\n"));
		if (is_env(env, c->args[i]))
			del_replace(env, c->args[i]);
	}
}
