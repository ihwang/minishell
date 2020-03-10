/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_old.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:18:31 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/10 17:29:52 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		make_old(void)
{
	int		i;
	char	**temp;
	char	*old;

	i = -1;
	while (g_env[++i])
		NULL;
	temp = (char**)malloc(sizeof(char*) * (i + 2));
	i = -1;
	while (g_env[++i])
		temp[i] = g_env[i];
	temp[i] = (char*)malloc(sizeof(char) * PATH_MAX);
	old = get_env("PWD=", VAL);
	ft_strcpy(temp[i], "OLDPWD=");
	ft_strcat(temp[i], old);
	temp[i + 1] = NULL;
	free(g_env);
	g_env = temp;
}
