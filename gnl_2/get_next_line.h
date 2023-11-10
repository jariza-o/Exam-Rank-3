/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jariza-o <jariza-o@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:05:21 by jariza-o          #+#    #+#             */
/*   Updated: 2023/11/10 11:41:51 by jariza-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef	GET_NEXT_LINE_H
# define	GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# include <fcntl.h>
# include <stdio.h>

# ifndef	BUFFER_SIZE
	# define BUFFER_SIZE 41
# endif

char	*get_next_line(int fd);

# endif