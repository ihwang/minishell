/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:52:07 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/03 20:01:34 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				is_in_path_sub(char *str, t_cmd *c)
{
	DIR			*dirp;
	t_dirent	*dir;

	if ((dirp = opendir(str)))
	{
		while ((dir = readdir(dirp)))
			if (!ft_strcmp(dir->d_name, c->comm))
				return (1);
		closedir(dirp);
	}
	return (0);
}

int				is_in_path(t_cmd *c, char ***env)
{
	int			i;
	int			nb;
	char		**split;

	split = ft_strsplit(get_env(env, "PATH=", VAL), ':');
	nb = -1;
	while (split[++nb])
		NULL;
	i = -1;
	while (++i < nb)
	{
		if (is_in_path_sub(split[i], c))
		{
			ft_strlst_del(&split, nb + 1);
			return (1);
		}
	}
	ft_strlst_del(&split, nb + 1);
	return (0);
}
