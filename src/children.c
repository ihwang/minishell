/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:14:05 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/05 14:28:52 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		make_child(t_cmd *c, char *path)
{
	pid_t	pid;
	int		wstat;

	pid = fork();
	if (pid == 0)
	{
		sig_controller(CHILD);
		ft_strcat(path, "/");
		ft_strcat(path, c->av[0]);
		if (access(path, X_OK))
		{
			ft_putstr(path);
			ft_putstr(": command not found\n");
			return (ft_strdel(&path));
		}
		execve(path, c->av, g_env);
		//Need to change struct of args
		//to args[0] == c->comm, args[1] == follwing
	}
	else if (pid > 0)
	{
		waitpid(pid, &wstat, 0);
	}
}
