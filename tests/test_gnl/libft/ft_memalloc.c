/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:45:51 by ihwang            #+#    #+#             */
/*   Updated: 2019/10/27 15:49:05 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *pt;

	pt = (void*)malloc(size);
	if (!pt)
		return (NULL);
	ft_bzero(pt, size);
	return (pt);
}
