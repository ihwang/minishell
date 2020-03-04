/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:14:05 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/04 17:29:05 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		make_chlid(t_cmd *c, char ***env, t_dirent *dir)
{
	pid_t	pid;
	int		wstat;

	pid = fork();
	if (pid == 0)
	{
		sig_controller(CHILD);

	}
	else if (pid > 0)
	{
		waitpid(pid, &wstat, 0);
	}
}
