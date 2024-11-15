/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:15:22 by moirhira          #+#    #+#             */
/*   Updated: 2024/11/14 15:15:24 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		calclen(char *str);
char	*find_newline(char *data, int ch);
char	*separate_line(char *data);
char	*update_buffer(char *data);
char	*my_strdup(char *src);
void	ft_copy(char *dest, const char *src);
void	ft_strcat(char *dest, const char *src);
char	*get_next_line(int fd);

#endif
