/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:05:10 by chchao            #+#    #+#             */
/*   Updated: 2022/09/28 14:29:37 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_map(t_mlx *env)
{
	env->map->c_pos[0] = 0.0;
	env->map->c_pos[1] = 0.0;
	env->map->c_dir[0] = 0.0;
	env->map->c_dir[1] = 0.0;
	env->map->tex_error = 0;
	env->map->m_y = 0;
	env->map->n_walls = 0;
	env->map->m_x = 0;
	env->map->fov = M_PI_4;
	env->map->far = 1000;
	env->map->layout = NULL;
	env->map->tex_data[0] = NULL;
	env->map->tex_data[1] = NULL;
	env->map->tex_data[2] = NULL;
	env->map->tex_data[3] = NULL;
}

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

int	get_map(t_map *map, char *file)
{
	int		i;
	int		j;
	char	**split;

	if (valid_size(map, file))
		return (-1);
	split = fill_blank(map, file);
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
