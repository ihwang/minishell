/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:48:26 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/06 15:21:54 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			print_no_cmd(char *str)
{
	ft_putstr(str);
	ft_putstr(": command not found\n");
}

void			print_unsetenv(char *str)
{
	ft_putstr("unsetenv: '");
	ft_putstr(str);
	ft_putstr("': not a valid indentifier\n");
}

int				there_is_d(t_cmd *c)
{
	if (access(c->av[1], F_OK))
	{
		ft_putstr("cd: ");
		ft_putstr(c->av[1]);
		ft_putstr(": No such file or directory\n");
		return (0);
	}
	else if (access(c->av[1], X_OK))
	{
		ft_putstr("cd: ");
		ft_putstr(c->av[1]);
		ft_putstr(": Permission denied\n");
		return (0);
	}
	return (1);
}

int				there_is_e(t_cmd *c)
{
	if (c->av[0][0] != '.' && c->av[0][0] != '/')
		return (0);
	else if (access(c->av[0], F_OK))
	{
		ft_putstr(c->av[0]);
		ft_putstr(": No such file or directory\n");
		return (0);
	}
	else if (access(c->av[0], X_OK))
	{
		ft_putstr(c->av[0]);
		ft_putstr(": Permission denied\n");
		return (0);
	}
	return (1);
}
