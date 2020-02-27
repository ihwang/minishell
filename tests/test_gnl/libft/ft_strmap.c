/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:39:49 by ihwang            #+#    #+#             */
/*   Updated: 2019/10/27 15:52:01 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*fresh;
	char	*c_fresh;

	fresh = (char*)malloc(ft_strlen(s) + 1);
	c_fresh = fresh;
	if (fresh && s)
	{
		while (*s)
			*c_fresh++ = f(*(s++));
		*c_fresh = '\0';
		return (fresh);
	}
	return (NULL);
}
