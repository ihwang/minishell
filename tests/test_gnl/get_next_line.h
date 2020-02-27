/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:29:51 by ihwang            #+#    #+#             */
/*   Updated: 2020/02/27 03:11:59 by tango            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 2
# define FD_SIZE 2000

# include "libft/libft.h"
# include <unistd.h>

int		get_next_line(const int fd, char **line);

#endif
