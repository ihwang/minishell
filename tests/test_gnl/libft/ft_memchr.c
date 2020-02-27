/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:20:27 by ihwang            #+#    #+#             */
/*   Updated: 2019/10/28 12:21:06 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *pt_s;
	unsigned char ch;

	pt_s = (unsigned char*)s;
	ch = (unsigned char)c;
	while (n-- > 0)
	{
		if (ch == *pt_s)
		{
			return ((void*)pt_s);
		}
		pt_s++;
	}
	return (NULL);
}
