/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intpt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 02:25:45 by ihwang            #+#    #+#             */
/*   Updated: 2020/03/02 04:17:19 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		tild_intp(char *str, char ***env)
{
	char	*home;
	char	temp[PATH_MAX];

	if (str[0] == '~' && (str[1] == '\0' || str[1] == '/'))
	{
		home = get_env(env, "HOME=");
		ft_bzero(temp, PATH_MAX);
		ft_strcat(temp, &str[1]);
		ft_strcpy(str, home);
		ft_strcat(str, temp);
	}
}	

void		dollar_sub(char *str, char ***env, char target[], int i)
{
	int		j;
	char	copy[PATH_MAX];

	j = i;
	while (ft_isalnum(str[++j]))
		NULL;
	ft_bzero(target, PATH_MAX);
	ft_strncpy(target, &str[i + 1], j - i - 1);
	ft_strcpy(copy, &str[j]);
	str[i] = '\0';
	if (get_env(env, ft_strcat(target, "=")))
	{
		str[i] = '\0';
		ft_strcat(str, get_env(env, target));
		ft_strcat(str, copy);
	}
	else
		ft_strcat(str, copy);
	///////////////////HERE!!!!!!!????????////////////
}

void		dollar_intp(char *str, char ***env)
{
	int		i;
	char	target[PATH_MAX];

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			dollar_sub(str, env, target, i);
		}
	}
}

/*			j = i;
			while (ft_isalnum(str[++j]))
				NULL;
			ft_bzero(target, PATH_MAX);
			ft_strncpy(target, &str[i + 1], j - i - 1);
			if (get_env(env, ft_strcat(target, "=")))
			{
				ft_strcpy(copy, &str[j]);
				str[i] = '\0';
				ft_strcat(str, get_env(env, target));
				ft_strcat(str, copy);
			}
		}
	}
}
	while (str[++i])
	{
		if (str[i] == '$')
		{
			j = -1;
			ft_strcpy(target, &str[i + 1]);
			while (ft_isalnum(target[++j]))
				NULL;
			ft_strcpy(copy, &target[j]);
			target[j] = '\0';
			if ((temp = get_env(env, ft_strcat(target, "="))))
			{
				ft_strcpy(str, temp);
				ft_strcat(str, copy);
			}
		}
	}
}
*/
