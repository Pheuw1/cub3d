/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchao <chchao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 13:03:22 by chchao            #+#    #+#             */
/*   Updated: 2022/08/07 13:03:24 by chchao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	square_wall(double wall[][2][2], int x, int y)
{
	wall[0][0][0] = x - 0.5;
	wall[0][0][1] = -y - 0.5;
	wall[0][1][0] = x + 0.5;
	wall[0][1][1] = -y - 0.5;
	wall[1][0][0] = x + 0.5;
	wall[1][0][1] = -y - 0.5;
	wall[1][1][0] = x + 0.5;
	wall[1][1][1] = -y + 0.5;
	wall[2][0][0] = x + 0.5;
	wall[2][0][1] = -y + 0.5;
	wall[2][1][0] = x - 0.5;
	wall[2][1][1] = -y + 0.5;
	wall[3][0][0] = x - 0.5;
	wall[3][0][1] = -y + 0.5;
	wall[3][1][0] = x - 0.5;
	wall[3][1][1] = -y - 0.5;
}

//n is -y s is +y w and e are same
void	convert_map_to_vecs(t_map *map)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < map->m_y)
	{
		x = -1;
		while (++x < map->m_x)
		{
			if (map->layout[x][y])
			{
				square_wall(&map->walls[map->n_walls], x, y);
				map->n_walls += 4;
			}
		}
	}
}

void	scale_vec_to(double *v, double c, double *res)
{
	double	x_unit[2];
	double	tmp[2];

	x_unit[0] = 1;
	x_unit[1] = 0;
	tmp[0] = v[0];
	tmp[1] = v[1];
	res[0] = c * cos(get_angle(x_unit, tmp));
	res[1] = c * sin(get_angle(x_unit, tmp));
}

/*
returns distance of intersection along v1 and v2
			v2
			^
			|
			|       
	p1------------->v1
			|
			|
			p2

*/
void	inter_dist(double p[2][2], double v[2][2], double *dist, double *wall_x)
{
	double	scale_v1;
	double	scale_v2;
	double	tmp[2];

	if (vec_cross(v[0], v[1]))
	{
		sub_vec(p[1], p[0], tmp);
		scale_v1 = vec_cross(tmp, v[1]) / vec_cross(v[0], v[1]);
		scale_v2 = vec_cross(tmp, v[0]) / vec_cross(v[1], v[0]);
		if (0 < scale_v1 && scale_v1 <= 1 && 0 < scale_v2 && scale_v2 <= 1)
		{
			*dist = (hypot(v[0][0] * scale_v1, v[0][1] * scale_v1));
			*wall_x = (hypot(v[1][0] * scale_v2, v[1][1] * scale_v2));
			return ;
		}
	}
	*dist = -1;
	*wall_x = -1;
}

int	collide(t_map *map, double size)
{
	double	v[2];
	int		i;
	double	tmp[5][2];
	double	d;

	i = -1;
	while (++i < map->n_walls)
	{
		sub_vec(map->walls[i][0], map->walls[i][1], tmp[0]);
		sub_vec(map->walls[i][0], map->c_pos, tmp[1]);
		d = (dot(tmp[0], tmp[1]));
		if (d >= 0 && d <= 1)
		{
			vec_mult(tmp[0], d, tmp[2]);
			add_vec(map->walls[i][0], tmp[2], tmp[3]);
			sub_vec(tmp[3], map->c_pos, v);
			if (hypot(v[0], v[1]) < size)
			{
				scale_vec_to(v, size - hypot(v[0], v[1]) + 0.0001, v);
				add_vec(map->c_pos, v, map->c_pos);
				return (1);
			}
		}
	}
	return (0);
}
