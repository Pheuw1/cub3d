/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:21:25 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/06/29 17:06:48 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "cub3d.h"

int	encode_rgb(int red, int green, int blue)
{
	return ((red % 256) << 16 | (green % 256) << 8 | (blue % 256));
}

void polar_to_cart(double *v, double *res)
{
	double tmp[2];
	
	tmp[0] = v[0];
	tmp[1] = v[1];
	res[0] = tmp[0]*cos(tmp[1]);
	res[1] = tmp[0]*sin(tmp[1]);
}
// returns distance to p1
// old name collision
/*
			v2
			^
			|
			|       
	p1------------->v1
			|
			|
		   p2

*/
void inter_dist(double p[2][2], double v[2][2], double *dist, double *wall_x)
{

	double scale_v1;
	double scale_v2;
	double tmp[2];
	
    if (vec_cross(v[0], v[1]))
	{
		sub_vec(p[1], p[0], tmp);
        scale_v1 = vec_cross(tmp, v[1]) / vec_cross(v[0], v[1]);
        scale_v2 = vec_cross(tmp, v[0]) / vec_cross(v[1], v[0]);
        if (0 < scale_v1 && scale_v1 <= 1 && 0 < scale_v2 && scale_v2 <= 1)// try removing scale2
		{
            *dist = (hypot(v[0][0] * scale_v1, v[0][1] * scale_v1));
			*wall_x = (hypot(v[1][0] * scale_v2, v[1][1] * scale_v2));
			return ;
		}
	}
	*dist = -1;
	*wall_x = -1;
}

// double inter_dist(double *p1, double *p2, double *v1, double *v2)
// {
// 	double scale_v1;
// 	double scale_v2;
// 	double tmp1[2];
// 	double tmp2[2];
	
//     if (vec_cross(v1, v2))
// 	{
// 		sub_vec(p2, p1, tmp1);
// 		sub_vec(p2, p1, tmp2);
//         scale_v1 = vec_cross(tmp1, v2) / vec_cross(v1, v2);
//         scale_v2 = vec_cross(tmp2, v1) / vec_cross(v2, v1);
//         if (0 < scale_v1 && scale_v1 <= 1 && 0 < scale_v2 && scale_v2 <= 1)// try removing scale2
//             return (hypot(v1[0] * scale_v1, v1[1] * scale_v1));
//     }
// 	return (-1);
// }

#include <stdio.h>
int collide(t_map *map, double size)
{
	double v[2];
	int i = -1;
	double tmp[5][2];
	double d;
	while (++ i < map->n_walls)
	{
		sub_vec(map->walls[i][0], map->walls[i][1],tmp[0]);
		sub_vec(map->walls[i][0], map->c_pos, tmp[1]);
		d = (dot(tmp[0], tmp[1]));
		if (d >= 0 && d <= 1)
		{
			scale_vec_by(tmp[0], d, tmp[2]);
			add_vec(map->walls[i][0], tmp[2], tmp[3]);
			sub_vec(tmp[3], map->c_pos, v);
			if (hypot(v[0], v[1]) < size)
			{
				scale_vec_to(v, size - hypot(v[0], v[1]) + 0.0001, v);
				// add_vec(map->walls[i][0], tmp[2], tmp[1]);
				add_vec(map->c_pos, v, map->c_pos);
				return (1);
			}
		}
	}
	return (0);
}
