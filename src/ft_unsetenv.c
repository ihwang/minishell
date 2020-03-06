/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:41:57 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/06 14:02:14 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		del_replace(char *str)
{
	int		nb;
	int		i;
	int		j;
	char	**temp;

	nb = -1;
	while (g_env[++nb])
		NULL;
	temp = (char**)malloc(sizeof(char*) * nb - 1);
	i = -1;
	j = 0;
	while (++i < nb - 1)
	{
		if (!ft_strstr(g_env[i], str))
		{
			temp[j] = (char*)malloc(PATH_MAX);
			ft_strcpy(temp[j++], g_env[i]);
		}
	}
	ft_strlst_del(&g_env, nb + 1);
	g_env = temp;
}

int			is_env(char *str)
{
	int		i;
	char	*dot;

	i = -1;
	while (g_env[++i])
	{
		dot = ft_strchr(g_env[i], '=');
		*dot = '\0';
		if (!ft_strcmp(g_env[i], str))
		{
			*dot = '=';
			return (1);
		}
		*dot = '=';
	}
	return (0);
}

void		ft_unsetenv(t_cmd *c)
{
	int		i;
	int		j;

	i = -1;
	while (++i < c->ac)
	{
//		tild_intp(c->av[i]);
//		dollar_intp(c->av[i]);
		j = -1;
		while (ft_isalnum(c->av[i][++j]))
			NULL;
		if (c->av[i][j] != '\0')
			return (ft_putstr("error\n"));
		if (is_env(c->av[i]))
			del_replace(c->av[i]);
	}
}
