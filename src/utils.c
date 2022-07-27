/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:16:29 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/06/29 17:37:23 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
void	init_render(t_render *render, void *mlx, t_mlx *env)
{
	render->mlx = mlx;
	render->env = env;
}

void 	print_vecs(t_map *map)
{
	int i;

	i = 0;
	while (i < map->n_walls)
	{
			printf("((%lf , %lf) , (%lf , %lf)),((%lf , %lf) , (%lf , %lf)),((%lf , %lf) , (%lf , %lf)),((%lf , %lf) , (%lf , %lf))\n",
					map->walls[i + 0][0][0],map->walls[i + 0][0][1],map->walls[i + 0][1][0],map->walls[i + 0][1][1],
					map->walls[i + 1][0][0],map->walls[i + 1][0][1],map->walls[i + 1][1][0],map->walls[i + 1][1][1],
					map->walls[i + 2][0][0],map->walls[i + 2][0][1],map->walls[i + 2][1][0],map->walls[i + 2][1][1],
					map->walls[i + 3][0][0],map->walls[i + 3][0][1],map->walls[i + 3][1][0],map->walls[i + 3][1][1]
					);
		i += 4;
	}
}

void	wall_square(double wall[][2][2], int x, int y)
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
	int 		x;
	int			y;

	x = -1;
	y = -1;
	map->n_walls = 0;
	while (++y < map->m_y)
	{
		x = -1;
		while (++x < map->m_x)
		{
			if (map->layout[x][y])
			{
				wall_square(&map->walls[map->n_walls],x ,y);
				map->n_walls += 4;
			}
		}
	}
}
