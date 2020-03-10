/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:14:36 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/10 17:09:58 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		get_prompt(void)
{
	char	*user;
	char	*pwd;
	char	*home;

	user = get_env("USER=", VAL);
	pwd = get_env("PWD=", VAL);
	home = get_env("HOME=", VAL);
	ft_putstr("Minishell ");
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

static char	**set_env(char **sample)
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

static int	minishell(void)
{
	char	*line;

	line = NULL;
	while (1)
	{
		sig_controller(PARENT);
		get_prompt();
		get_next_line(0, &line);
		is_eof(line) ? parse_line(&line) : ft_exit(NULL);
	}
	return (0);
}

int			main(int ac, char **av, char **envp)
{
	ac = 0;
	av = NULL;
	g_env = set_env(envp);
	return (minishell());
}
