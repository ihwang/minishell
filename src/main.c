/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:14:36 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/03 01:07:05 by ihwang           ###   ########.fr       */
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
	char	*user;
	char	*pwd;
	char	*home;

	user = get_env(&env, "USER=", VAL);
	pwd = get_env(&env, "PWD=", VAL);
	home = get_env(&env, "HOME=", VAL);
	if (!ft_strcmp(pwd, home))
		ft_putstr(pwd);
	else if (ft_strstr(pwd, home))
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
		parse_line(&line, &env);
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
