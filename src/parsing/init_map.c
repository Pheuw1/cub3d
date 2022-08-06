/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:01:49 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/08/06 20:24:27 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_layout(t_map *map)
{
	int	i;
	int	j;

	map->layout = (int **)malloc(map->m_x * sizeof(int *));
	i = -1;
	while (++i < map->m_x)
		map->layout[i] = (int *)malloc(map->m_y * sizeof(int));
	i = -1;
	j = -1;
	while (++i < map->m_x)
	{
		j = -1;
		while (++j < map->m_y)
			map->layout[i][j] = 0;
	}
}

/*returns index to texture  
color_ns = colors[0] if ns > 0 else colors[1]  # n and s
color_we = colors[2] if we > 0 else colors[3]  # w and e
return (blend_colors(color_ns, abs(ns), color_we, abs(we)))*/
int	det_cardinals(double wall[2][2])
{
	double	units[2][2];
	double	a;
	double	v[2];
	double	tmp[2];

	units[0][0] = 1;
	units[0][1] = 0;
	units[1][0] = 0;
	units[1][1] = 1;
	sub_vec(wall[0], wall[1], tmp);
	v[0] = cos(get_angle(units[0], tmp) + M_PI_2);
	v[1] = sin(get_angle(units[0], tmp) + M_PI_2);
	if (ft_abs_d(dot(v, units[1])) > ft_abs_d(dot(v, units[0])))
	{
		if (dot(v, units[1]) > 0)
			return (1);
		return (0);
	}
	else
	{
		if (dot(v, units[0]) > 0)
			return (3);
		return (2);
	}
	return (0);
}

int	get_color(char *line)
{
	char	**tmp;
	int		vals[3];

	tmp = ft_split(line, " ,()");
	if (tmp && tmp[0] && tmp[1] && tmp[2] && !tmp[3])
	{
		vals[0] = ft_atoi(tmp[0]);
		vals[1] = ft_atoi(tmp[1]);
		vals[2] = ft_atoi(tmp[2]);
		ft_freepp((void *)tmp);
	}
	else
	{
		ft_freepp((void *)tmp);
		return (ft_error("cub3d", "invalid color format", -1, NULL));
	}
	if ((vals[0] < 0 || vals[0] > 255) || (vals[1] < 0 || vals[1] > 255)
		|| (vals[2] < 0 || vals[2] > 255))
		return (ft_error("cub3d", "invalid color format", -1, NULL));
	return (encode_rgb(vals[0], vals[1], vals[2]));
}

int	get_map(t_map *map, char *file)
{
	int		i;
	int		j;
	char	**split;

	if (is_valid_map_get_sizes(map, file))
		return (-1);
	split = map_makerect(map, file);
	free(file);
	init_layout(map);
	i = -1;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
		{
			if (split[i][j] == '0' || get_camdir_pos(map, split[i][j], i, j))
				map->layout[j][i] = 0;
			else
				map->layout[j][i] = 1;
		}
	}
	ft_freepp((void *)split);
	if (break_free(map))
		return (ft_error("cub3d", "map is not closed", -1, NULL));
	return (0);
}

int	get_camdir_pos(t_map *map, char card, int i, int j)
{
	if (card == 'N')
	{
		map->c_dir[0] = 0.0;
		map->c_dir[1] = 1.0;
	}
	else if (card == 'S')
	{
		map->c_dir[0] = 0.0;
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
