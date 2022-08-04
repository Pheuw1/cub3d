/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:35:51 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/06/29 17:42:15 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	render_background(t_mlx *env)
{
	int	i;
	int	j;

	i = 0;
	while (++i < (WIDTH))
	{
		j = 0;
		while (++j < (HEIGHT) / 2)
			set_pixel(env, i, j, env->map->floor);
		while (++j < (HEIGHT))
			set_pixel(env, i, j, env->map->ceil);
	}
}

//sets pixel through window coords
void	set_pixel(t_mlx *env, int w_x, int w_y, int color)
{
	char	*dst;

	if (!env->addr || w_x > WIDTH || w_x < 0 || w_y > HEIGHT || w_y < 0)
		return ;
	dst = env->addr + (w_y * env->size_line + w_x * (env->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


void	draw_col(t_mlx *env, double dist, int  x)
{
	int		start;
	int		end;
	double	scale;
	
	if (dist > 0)
	{
		scale = ft_min_d((HEIGHT), HEIGHT / dist);
		start = (int)((double)(HEIGHT) / 2 - scale / 2);
		end	= (int)((double)(HEIGHT) / 2 + scale / 2);
		while (start <= end)
		{
			set_pixel(env, x, start, encode_rgb(100,100,200));
			start++;
		}
	}
}

//returns index to texture
// color_ns = colors[0] if ns > 0 else colors[1]  # n and s
// color_we = colors[2] if we > 0 else colors[3]  # w and e
// return (blend_colors(color_ns, abs(ns), color_we, abs(we)))
int det_cardinals(double wall[2][2])
{
	double units[2][2];
	double a;
	double v[2];
	double tmp[2];
	
	units[0][0] = 1;
	units[0][1] = 0;
	units[1][0] = 0;
	units[1][1] = 1;
	sub_vec(wall[0],wall[1],tmp);
    a = get_angle(units[0], tmp) + M_PI_2;
    v[0] = cos(a);
	v[1] = sin(a);
	if (ft_abs_d(dot(v,units[1])) > ft_abs_d(dot(v,units[0])))
	{
		if (dot(v,units[1]) > 0)
			return (1);
		return (0);
	}
	else
	{
		if (dot(v,units[0]) > 0)
			return (3);
		return (2);
	}
	return (0);
}

//dist 0 is how far wall is, dist 1 is coord along texture
void draw_col_tex(t_mlx *env, int x, int idx, double *dists)
{
	int 	color;
	int 	height[2];
	double	scale;
	double	row;
	double 	step;

	if (dists[0] < 0 || dists[1] < 0)
		return ;
	scale =  (HEIGHT / dists[0]);
	height[0] = (int)((double)(HEIGHT) / 2 - scale / 2);
	height[1] = (int)((double)(HEIGHT) / 2 + scale / 2);
	row  = 0;
	step = (env->map->t_w / scale); //* (HEIGHT / env->map->t_w));
	while (height[0] <= height[1])
	{
		color = *((int *)(env->map->textures[idx]->data) + (int)(row) * env->map->t_w + (int)(dists[1] * env->map->t_w));
		set_pixel(env, x, height[0], color);
		row += step;
		height[0]++;
	}	
}

void draw_closest_wall(t_mlx *env, double *ray, int x)
{
	double 	dists[2];
	double	tmp[2];
	double 	p[2][2];
	double 	v[2][2];
	int		i[2];

	i[0] = -1;
	p[0][0] = env->map->c_pos[0];
	p[0][1] = env->map->c_pos[1];
	v[0][0] = ray[0];
	v[0][1] = ray[1];
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
	if (dists[0] > 0)
		draw_col_tex(env, x, i[1], dists);
		// draw_col(env, dists[0], x);
}

void cast_rays(t_mlx *env)
{
	double 	a;
	double	v[2];
	double	cast[3];

	a = get_abs_angle(env->map->c_dir);
	cast[0] =  a - env->map->fov/2;
	cast[1] =  a + env->map->fov/2;
	cast[2] =  env->map->fov / (WIDTH * 1.274);
	while (cast[0] <= cast[1])
	{
		v[0] =  -env->map->far * cos(cast[0]);
		v[1] =	env->map->far * sin(cast[0]);
		draw_closest_wall(env, v, (int)((cast[0] - a + env->map->fov/2) * WIDTH* 1.274)),
		cast[0] += cast[2];
	}
}

void rotate(t_mlx *env)
{
	if (env->keys.left)
		rot_vec(env->map->c_dir, M_PI / 32, env->map->c_dir);
	else if (env->keys.right)
		rot_vec(env->map->c_dir, -M_PI / 32, env->map->c_dir);
}

void move(t_mlx *env)
{
	double tmp[2];

	if (env->keys.w)
	{
		scale_vec_to(env->map->c_dir, 0.1, tmp);
	    add_vec(env->map->c_pos, tmp, env->map->c_pos);
    }
	else if (env->keys.s)
	{
		scale_vec_to(env->map->c_dir, -0.1, tmp);
	    add_vec(env->map->c_pos, tmp, env->map->c_pos);
	}
	if (env->keys.a)
	{
		rot_vec(env->map->c_dir, M_PI / 2, tmp);
		scale_vec_to(tmp, 0.05, tmp);
		add_vec(env->map->c_pos, tmp, env->map->c_pos);
	}
	else if (env->keys.d)
	{
		rot_vec(env->map->c_dir, -M_PI / 2, tmp);
		scale_vec_to(tmp, 0.05, tmp);
		add_vec(env->map->c_pos, tmp, env->map->c_pos);
	}
}

int	frame(t_mlx *env)
{	
	if (!collide(env->map, 0.25))
	{
		if (env->keys.left || env->keys.right)
			rotate(env);
		if (env->keys.w || env->keys.a
				|| env->keys.s || env->keys.d)
				move(env);
		render_background(env);
		cast_rays(env);
		draw_map_circle(env, WIDTH - HEIGHT / 8, HEIGHT / 8, HEIGHT / 8);
		mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
	}
	return (0);
}

// int params(char **)