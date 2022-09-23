/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:29:28 by chchao            #+#    #+#             */
/*   Updated: 2022/09/23 16:46:40 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_empty(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
		if (s[i] != '\n' && s[i] != ' ' && s[i] != '	')
			return (0);
	return (1);
}

void	*open_tex(t_mlx *env, char *path, int idx)
{
	int		i;
	void	*ret;

	i = -1;
	while (path[++i])
		if (path[i] != ' ')
			break ;
	path = &path[i];
	i = -1;
	while (path[++i])
		if (path[i] == ' ' || path[i] == '\n')
			break ;
	path = ft_substr(path, 0, i);
	if (!env->map->tex_data[idx])
		ret = mlx_xpm_file_to_image(env->mlx, path,
				&env->map->t_w, &env->map->t_h);
	free(path);
	if (!ret)
		env->map->tex_error = 1;
	else
		env->map->tex_data[idx] = (int *)mlx_get_data_addr(ret, &i, &i, &i);
	return (ret);
}

int	get_textures_colors(t_mlx *env, int fd, int count)
{
	char	*line;

	line = get_next_line(fd);
	while (line && count < 6)
	{
		if (ft_strstr(line, "NO") && ++(count))
			env->map->textures[0] = open_tex(env, ft_strstr(line, "NO") + 2, 0);
		else if (ft_strstr(line, "SO") && ++(count))
			env->map->textures[1] = open_tex(env, ft_strstr(line, "SO") + 2, 1);
		else if (ft_strstr(line, "WE") && ++(count))
			env->map->textures[2] = open_tex(env, ft_strstr(line, "WE") + 2, 2);
		else if (ft_strstr(line, "EA") && ++(count))
			env->map->textures[3] = open_tex(env, ft_strstr(line, "EA") + 2, 3);
		else if (ft_strstr(line, "F") && ++(count))
			env->map->floor = get_color(ft_strstr(line, "F") + 1);
		else if (ft_strstr(line, "C") && ++(count))
			env->map->ceil = get_color(ft_strstr(line, "C") + 1);
		else if (!is_empty(line))
			return (ft_error("cub3d", "invalid config format", -1, line));
		free(line);
		if (count < 6)
			line = get_next_line(fd);
	}
	return (0);
}
