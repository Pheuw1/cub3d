/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:04:48 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/08/06 20:22:21 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_empty(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
		if (s[i] != '\n' || s[i] != ' ' || s[i] != '	')
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
	ret = mlx_xpm_file_to_image(env->mlx, path, &env->map->t_w, &env->map->t_h);
	env->map->tex_data[idx] = (int *)mlx_get_data_addr(ret, &i, &i, &i);
	free(path);
	if (!ret)
		env->map->tex_error = 1;
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

char	**map_makerect(t_map *map, char *file)
{
	int		i;
	int		j;
	char	**split;
	char	end[100000];
	char	*tmp;

	split = ft_split(file, "\n");
	i = -1;
	while (split && split[++i])
	{
		if (is_empty(split[i]))
			split = ft_remove_from_strarr(split, i);
		else if (ft_strlen(split[i]) < map->m_x)
		{
			j = -1;
			while (++j < map->m_x - ft_strlen(split[i]))
				end[j] = '0';
			end[j] = 0;
			tmp = ft_strjoin(split[i], end);
			free(split[i]);
			split[i] = tmp;
		}
	}
	i = -1;
	return (split);
}

int	parse_input(t_mlx *env, char *config)
{
	char	*file;
	char	*line;
	char	*tmp;
	int		fd;

	if (ft_strcmp(&config[ft_strlen(config) - 4], ".cub"))
		return (ft_error("cube3d", "invalid config file extension", -1, NULL));
	fd = open(config, O_RDONLY);
	if (fd < 0 || get_textures_colors(env, fd, 0) || env->map->floor < 0
		|| env->map->ceil < 0)
		return (-1);
	if (env->map->tex_error)
		return (ft_error("cube3d", "textures couldn't be loaded", -1, NULL));
	file = NULL;
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(file, line);
		free(file);
		file = tmp;
		free(line);
		line = get_next_line(fd);
	}
	return (get_map(env->map, file));
}
