/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:01:49 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/06/30 14:21:53 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_empty(char *s)
{
	int i;

	i = -1;
	while (s && s[++i])
		if (s[i]!= '\n' || s[i]!= ' ' || s[i] != '	')
			return (0);
	return (1);
}

int	get_color(char *line)
{
	char  **tmp;
	int 	vals[3];

	tmp = ft_split(line, " ,()");
	if (tmp && tmp[0] && tmp[1] && tmp[2] && !tmp[3])
	{
		vals[0] = ft_atoi(tmp[0]);
		vals[1] = ft_atoi(tmp[1]);
		vals[2] = ft_atoi(tmp[2]);
	}
	else
		return (ft_error("cub3d", "invalid color format", -1));
	ft_freepp((void *)tmp);
	if   ((vals[0] < 0 || vals[0] > 255)
		||(vals[1] < 0 || vals[1] > 255)
		||(vals[2] < 0 || vals[2] > 255))
		return (ft_error("cub3d", "invalid color format", -1));
	return(encode_rgb(vals[0],vals[1],vals[2]));
}

t_img *open_texture(t_mlx *env, char *path)
{
	int i;
	t_img *ret;
	
	i = -1;
	while (path[++i])
		if (path[i] != ' ')
			break ;
	path = &path[i];
	i = -1;
	while (path[++i])
		if (path[i] == ' ' || path[i] == '\n')
			break;
	path = ft_substr(path, 0, i);\
	ret = ((t_img *)mlx_xpm_file_to_image(env->mlx, path, &env->map->t_w, &env->map->t_w));
	free(path);
	if (!ret)
		env->map->tex_error = 1;
	return (ret);
}

int	get_textures_colors(t_mlx *env, int fd)
{
	char	*line;
	int		found;

	found = 0;
	line = get_next_line(fd);
	while (line && found < 6)
	{
		if (!ft_strncmp(line, "NO ", 3) && ++(found))
			env->map->textures[0] = open_texture(env, &line[3]);
		else if (!ft_strncmp(line, "SO ", 3) && ++(found))
			env->map->textures[1] = open_texture(env, &line[3]);
		else if (!ft_strncmp(line, "WE ", 3) && ++(found))
			env->map->textures[2] = open_texture(env, &line[3]);
		else if (!ft_strncmp(line, "EA ", 3) && ++(found))
			env->map->textures[3] = open_texture(env, &line[3]);
		else if (!ft_strncmp(line, "F ", 2) && ++(found))
			env->map->floor = get_color(&line[2]);
		else if (!ft_strncmp(line, "C ", 2) && ++(found))
			env->map->ceil = get_color(&line[2]);
		else if (!is_empty(line))
			return (ft_error("cub3d", "invalid config format", -1));
		free(line);
		if (found < 6)
			line = get_next_line(fd);
	}
	return (0);
}


int is_valid_map_get_sizes(t_map *map, char *file)
{
	int	i;
	int len;
	int pos;

	len = 0;
	pos = 0;
	while (file[++i])
	{
		if (file[i] == '\n')
		{
			map->m_y++;
			map->m_x = ft_max(map->m_x, len);
			len = -1;
		}
		if (file[i] == 'N' || file[i] == 'S' || file[i] == 'W' || file[i] == 'E')
			pos = 1;
		else if (file[i] == '0' || file[i] == ' ')
			file[i] = '0';
		else if (file[i] != '1' && file[i] != '\n')
			return (ft_error("cub3d", "invalid map format", -1));
		len++;
	}
	map->m_y++;
	if (!pos)
		return (ft_error("cub3d", "player position not found", -1));
	return (0);
}

char **cleanup_MakeRect(t_map *map, char *file)
{
	int		i;
	int		j;
	char	**split;
	char	end[10000];
	char 	*tmp;

	split = ft_split(file, "\n");
	i = -1;
	while (split && split[++i])
	{
		if (is_empty(split[i]))
			split  = ft_remove_from_strarr(split, i);
		else if (ft_strlen(split[i]) < map->m_x)
		{
			j = -1;
			while (++j < map->m_x - ft_strlen(split[i]))
				end[j] = ' ';
			end[j] = 0;
			tmp = ft_strjoin(split[i], end);
			free(split[i]);
			split[i] = tmp;
		}
	}
	i = -1;
	return (split);
}

int	get_CamDir_and_pos(t_map *map, char card, int i, int j)
{
	if (card == 'N')
	{
		map->c_dir[0] = 0.0;
		map->c_dir[1] = 1.0;
	}
	else if (card == 'S')
	{
		map->c_dir[0] =  0.0;
		map->c_dir[1] = -1.0;
	}
	else if (card == 'W')
	{
		map->c_dir[0] = -1.0;
		map->c_dir[1] = 0.0;
	}
	else if (card == 'E')
	{
		map->c_dir[0] = 1.0;
		map->c_dir[1] = 0.0;
	}
	else
		return (0);
	map->c_pos[0] = j;
	map->c_pos[1] = -i;  
	return (1);
}

int search(t_map *map, int **vis, int x, int y)
{
    if (vis[x][y] || map->layout[x][y])
        return (0);
    vis[x][y] = 1;
    if (!((x + 1) < map->m_x) || !((x - 1) >= 0)  
        || !((y + 1) < map->m_y)  || !((y - 1) >= 0))
        return (-1);
    if ((search(map, vis, x + 1, y)) || (search(map, vis, x - 1, y)) || (search(map, vis, x, y + 1)) || (search(map, vis, x, y - 1)))
        return (-1);
    return (0);
}

int break_free(t_map *map)
{
    int i;
    int j;
    int **vis;
	int ret;

    vis = (int **)malloc(map->m_x * sizeof(int *));
    i = -1;
    while (++i < map->m_x)
        vis[i] = (int *)malloc(map->m_y * sizeof(int));
    i = -1;
    j = -1;
    while (++i < map->m_x)
    {
        j = -1;
        while(++j < map->m_y)
            vis[i][j] = 0;
    }
	ret = search(map, vis, map->c_pos[0], -map->c_pos[1]);
	i = -1;
    while (++i < map->m_x)
		free(vis[i]);
	free(vis);
	return(ret);
}

int	get_map(t_map *map, char *file)
{
	int	i;
	int j;
	char **split;
	
	if (is_valid_map_get_sizes(map, file))
		return (-1);
	split = cleanup_MakeRect(map, file);
	free(file);
	map->layout = (int **)malloc(map->m_x * sizeof(int*));
	i = -1;
	while (++i < map->m_x)
		map->layout[i] = (int *)malloc(map->m_y * sizeof(int));
	i = -1;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (split[i][j] == '0' || get_CamDir_and_pos(map, split[i][j], i, j))
				map->layout[j][i] = 0;
			else if (split[i][j] == '1')
				map->layout[j][i] = 1;
		}
	}
	ft_freepp((void *)split);
	if (break_free(map))
		return (ft_error("cub3d", "map is not closed", -1));
	return (0);
}

int	parse_input(t_mlx *env, char *config)
{
	char  	*file;
	char	*line;
	char 	*tmp;
	int		fd;

	if (ft_strcmp(&config[ft_strlen(config) - 4], ".cub"))
		return (ft_error("cube3d", "invalid config file extension", -1));
	fd = open(config, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (get_textures_colors(env, fd))
		return (-1);
	if (env->map->tex_error) 
		return (ft_error("cube3d", "textures couldn't be loaded", -1));
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
