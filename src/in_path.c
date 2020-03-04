/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:52:07 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/04 16:30:31 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_dirent		*is_in_path_sub(char *str, t_cmd *c)
{
	DIR			*dirp;
	t_dirent	*dir;

	if ((dirp = opendir(str)))
	{
		while ((dir = readdir(dirp)))
		{
			if (!ft_strcmp(dir->d_name, c->comm))
			{
				closedir(dirp);
				return (dir);
			}
		}
		closedir(dirp);
	}
	return (NULL);
}

t_dirent		*is_in_path(t_cmd *c)
{
	int			i;
	int			nb;
	char		**split;
	t_dirent	*dir;

	split = ft_strsplit(get_env("PATH=", VAL), ':');
	nb = -1;
	while (split[++nb])
		NULL;
	i = -1;
	while (++i < nb)
	{
		if ((dir = is_in_path_sub(split[i], c)))
		{
			ft_strlst_del(&split, nb + 1);
			return (dir);
		}
	}
	ft_strlst_del(&split, nb + 1);
	return (NULL);
}
