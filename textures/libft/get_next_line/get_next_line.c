/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 15:51:10 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/06/30 13:25:34 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char	*find_line(char **fs)
{
	char	*tmp;
	char	*line;
	ssize_t	line_len;

	line_len = 0;
	while ((*fs)[line_len] != '\n' && (*fs)[line_len])
		line_len++;
	if ((*fs)[line_len])
	{
		line = ft_substr((*fs), 0, line_len + 1);
		tmp = ft_strdup(&((*fs)[line_len + 1]));
		ft_strdel(fs);
		*fs = tmp;
		if (!((*fs)[0]))
			ft_strdel(fs);
	}
	else
	{
		line = ft_strdup((*fs));
		ft_strdel(fs);
	}
	return (line);
}

char	*ret_line(char **fs, ssize_t r)
{
	if (r < 0 || !fs)
		return (NULL);
	if (!ft_strlen(*fs))
	{
		ft_strdel(fs);
		return (NULL);
	}
	return (find_line(fs));
}

char	*get_next_line(int fd)
{
	static char	*file_slice[MAX_FD] = {NULL};
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		r;

	if (fd < 0)
		return (NULL);
	r = 1;
	while (r > 0 && !ft_strchr(file_slice[fd], '\n'))
	{
		r = read(fd, buffer, BUFFER_SIZE);
		buffer[r] = '\0';
		if (file_slice[fd] == NULL && r >= 0)
			file_slice[fd] = ft_strdup(buffer);
		else if (r >= 0)
		{
			tmp = ft_strjoin(file_slice[fd], buffer);
			free(file_slice[fd]);
			file_slice[fd] = tmp;
		}
	}
	return (ret_line(&file_slice[fd], r));
}
