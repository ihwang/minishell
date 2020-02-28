/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:14:36 by ihwang            #+#    #+#             */
/*   Updated: 2020/02/28 23:49:46 by tango            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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


void		get_prompt(char **env)
{
	int		i;
	char	*user;
	char	*pwd;
	char	*home;

	i = -1;
	while (env[++i])
	{
		if (ft_strstr(env[i], "USER="))
			user = ft_strchr(env[i], '=') + 1;
		else if (ft_strstr(env[i], "PWD="))
			pwd = ft_strchr(env[i], '=') + 1;
		else if (ft_strstr(env[i], "HOME="))
			home = ft_strchr(env[i], '=') + 1;
	}
	if (ft_strstr(pwd, home))
	{
		ft_putstr("~");
		ft_putstr(ft_strstr_e(pwd, home));
	}
	else
		ft_putstr(pwd);
	ft_putstr(" ");
	ft_putstr(user);
	ft_putstr("$ ");
}	

void			signal_handler(int sig)
{
	int			a;
	extern char	**environ;

	a = sig;
	putchar('\n');
	get_prompt(environ);
	signal(SIGINT, signal_handler);
}

int			minishell(char **env)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, signal_handler);
		get_prompt(env);
		get_next_line(0, &line);
		parse_line(&line, env);
	}
	return (0);
}

int			main(int ac, char **av, char **envp)
{
	char	**env;
ac = 0;
av = NULL;

	env = set_env(envp);
	return (minishell(env));
}
