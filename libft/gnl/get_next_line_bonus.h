/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:50:54 by mamesser          #+#    #+#             */
/*   Updated: 2023/07/13 15:39:18 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen2(const char *s);
char	*ft_strjoin_mod(char *s1, char *s2);
char	*ft_strchr_mod(const char *s, int c, size_t *line_len);
char	*get_next_line(int fd);
char	*ft_free(char *collector, char *buf, int flag_both);

#endif