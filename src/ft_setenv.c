/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 00:41:54 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/04 16:24:56 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		add_env(char *arg)
{
	int		i;
	char	**temp;

	i = -1;
	while (g_env[++i])
		NULL;
	temp = (char**)malloc(sizeof(char*) * (i + 2));
	i = -1;
	while (g_env[++i])
		temp[i] = g_env[i];
	temp[i] = (char*)malloc(sizeof(char) * PATH_MAX);
	ft_strcpy(temp[i], arg);
	temp[i + 1] = NULL;
	free(g_env);
	g_env = temp;
}

void		ft_setenv_sub(char *arg)
{
	char	**split;
	char	*var;
	int		j;

	split = ft_strsplit(arg, '=');
	if ((var = get_env(split[0], VAL)))
	{
		var++;
		j = 0;
		var[0] = '\0';
		while (split[++j])
			ft_strcat(var, split[j]);
	}
	else
		add_env(arg);
	j = -1;
	while (split[++j])
		NULL;
	ft_strlst_del(&split, j + 1);
}

void		ft_setenv(t_cmd *c)
{
	int		i;
	int		j;

	i = -1;
	while (++i < c->arg_nb)
	{
		tild_intp(c->args[i]);
		dollar_intp(c->args[i]);
		j = -1;
		while (ft_isalnum(c->args[i][++j]))
			NULL;
		if (c->args[i][j] =='\0')
			return ;
		else if (c->args[i][j] != '=' || j == 0)
			return (ft_putstr("errro\n"));
		else
			ft_setenv_sub(c->args[i]);
	}
}
