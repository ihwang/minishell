/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:14:36 by ihwang            #+#    #+#             */
/*   Updated: 2020/02/26 22:51:33 by tango            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		**set_env(char **sample)
{
	char	**env;
	int		i;

	i = -1;
	while (sample[++i])
		NULL;
	env = (char**)malloc(sizeof(char*) * (i + 1));
	i = -1;
	while (sample[++i])
	{
		env[i] = (char*)malloc(sizeof(char) * PATH_MAX);
		ft_strcat(env[i], sample[i]);
	}
	env[i] = NULL;
	return (env);
}

int			minishell(char **env)
{
	while ()
	{



	}
}

int			main(int argc, char **argv, char **argp char **envp)
{
	char	**env;
	env = set_env(envp);
	return (minishell(env));
}
