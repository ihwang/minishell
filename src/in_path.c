/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:52:07 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/06 15:00:13 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		is_in_path_sub(char *str, t_cmd *c)
{
	DIR			*dirp;
	t_dirent	*dir;

	if ((dirp = opendir(str)))
	{
		while ((dir = readdir(dirp)))
		{
			if (!ft_strcmp(dir->d_name, c->av[0]))
			{
				closedir(dirp);
				return (1);
			}
		}
		closedir(dirp);
	}
	return (0);
}

char			*is_in_path(t_cmd *c)
{
	int			i;
	int			nb;
	char		**split;
	char		*path;

	if (c->av[0][0] == '.' || c->av[0][0] == '/')
		return (NULL);
	split = ft_strsplit(get_env("PATH=", VAL), ':');
	nb = -1;
	while (split[++nb])
		NULL;
	i = -1;
	while (++i < nb)
	{
		if (is_in_path_sub(split[i], c))
		{
			path = ft_strnew(PATH_MAX);
			ft_strcpy(path, split[i]);
			ft_strlst_del(&split, nb + 1);
			return (path);
		}
	}
	ft_strlst_del(&split, nb + 1);
	return (NULL);
}
