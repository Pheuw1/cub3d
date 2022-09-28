/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchao <chchao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:35:51 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/08/07 15:34:58 by chchao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_mlx *env, int *pos, int size, int color)
{
	int	start[2];

	start[1] = ft_max(0, pos[1] - size / 2) - 1;
	while (++start[1] < HEIGHT && start[1] < pos[1] + size / 2)
	{
		start[0] = ft_max(0, pos[0] - size / 2) - 1;
		while (++start[0] < WIDTH && start[0] < pos[0] + size / 2)
			set_pixel(env, start[0], start[1], color);
	}
}

void	draw_circle(t_mlx *env, int *pos, int r, int color)
{
	int	i;
	int	j;

	i = -1 - r;
	while (++i < r)
	{
		j = -1 - r;
		while (++j < r)
			if (sqrt(i * i + j * j) < r)
				set_pixel(env, pos[0] + i, pos[1] + j, color);
	}
}

void	draw_closest_wall(t_mlx *env, double *ray, int x)
{
	double	dists[2];
	double	tmp[2];
	double	p[2][2];
	double	v[2][2];
	int		i[2];

	i[0] = -1;
	vec_equal(p[0], env->map->c_pos);
	vec_equal(v[0], ray);
	dists[0] = env->map->far;
	while (++(i[0]) < env->map->n_walls)
	{
		p[1][0] = env->map->walls[i[0]][0][0];
		p[1][1] = env->map->walls[i[0]][0][1];
		sub_vec(env->map->walls[i[0]][0], env->map->walls[i[0]][1], v[1]);
		inter_dist(p, v, &tmp[0], &tmp[1]);
		if (tmp[0] > 0 && tmp[0] < dists[0])
		{
			i[1] = det_cardinals(env->map->walls[i[0]]);
			dists[0] = tmp[0];
			dists[1] = tmp[1];
		}
	}
	if (dists[0] > 0 && dists[0] < env->map->far)
		draw_col_tex(env, x, i[1], dists);
}

void	cast_rays(t_mlx *env)
{
	double	a;
	double	v[2];
	double	cast[3];

	a = get_abs_angle(env->map->c_dir);
	cast[0] = a - env->map->fov / 2;
	cast[1] = a + env->map->fov / 2;
	cast[2] = env->map->fov / (WIDTH * 1.274);
	while (cast[0] <= cast[1])
	{
		v[0] = -env->map->far * cos(cast[0]);
		v[1] = env->map->far * sin(cast[0]);
		draw_closest_wall(env, v,
			(int)((cast[0] - a + env->map->fov / 2) * WIDTH * 1.274));
			cast[0] += cast[2];
	}
}

int	frame(t_mlx *env)
{
	if (!collide(env->map, 0.25))
	{
		if (env->keys.left || env->keys.right)
			rotate(env);
		if (env->keys.w || env->keys.a || env->keys.s || env->keys.d)
			move(env);
		render_background(env);
		cast_rays(env);
		draw_map(env, WIDTH - HEIGHT / 8, HEIGHT / 8, HEIGHT / 8);
		mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
	}
	return (0);
}
