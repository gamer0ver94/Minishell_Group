/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:52:08 by dpaulino          #+#    #+#             */
/*   Updated: 2022/03/30 14:52:08 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
#define BUFFER_SIZE 1

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		verify_buffer(char *str, char c);
char	*ft_clean(char *stash, char *buffer);
void	*ft_calloc(size_t counter, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc_gnl(size_t counter, size_t size);
#endif