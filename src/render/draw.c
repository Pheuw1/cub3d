/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:35:51 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/08/06 17:30:19 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int	encode_rgb(int red, int green, int blue)
{
	return ((red % 256) << 16 | (green % 256) << 8 | (blue % 256));
}

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

void	set_pixel(t_mlx *env, int w_x, int w_y, int color)
{
	char	*dst;

	if (!env->addr || w_x > WIDTH || w_x < 0 || w_y > HEIGHT || w_y < 0)
		return ;
	dst = env->addr + (w_y * env->size_line + w_x * (env->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

//dist 0 is how far wall is, dist 1 is coord along texture
void	draw_col_tex(t_mlx *env, int x, int idx, double *dists)
{
	int		color;
	int		height[2];
	double	scale;
	double	row;
	double	step;

	if (dists[0] < 0 || dists[1] < 0)
		return ;
	scale = (HEIGHT / dists[0]);
	height[0] = (int)((double)(HEIGHT) / 2 - scale / 2);
	height[1] = (int)((double)(HEIGHT) / 2 + scale / 2);
	row = 0;
	step = (env->map->t_w / scale);
	while (height[0] <= height[1])
	{
		color = *((int *)(env->map->tex_data[idx])
				+ (int)(row)*env->map->t_w + (int)(dists[1] * env->map->t_h));//
		set_pixel(env, x, height[0], color);
		row += step;
		height[0]++;
	}
}
