/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:32:40 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/08/06 20:33:06 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"
# define BUFFER_SIZE 1024
# define MAX_FD      1024

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void	ft_strdel(char **as);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*find_line(char **fs);
char	*get_next_line(int fd);
#endif