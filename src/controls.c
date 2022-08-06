/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:32:21 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/06/29 17:06:45 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	init_keys(t_K_data *keys)
{
	keys->left = 0;
	keys->right = 0;
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
}

int	ft_press(int keycode, t_mlx *env)
{
	if (keycode == K_ESCAPE)
		exit_mlx(env);
	if (keycode == K_RIGHT)
		env->keys.right = 1;
	if (keycode == K_LEFT)
		env->keys.left = 1;
	if (keycode == K_W)
		env->keys.w = 1;
	if (keycode == K_A)
		env->keys.a = 1;
	if (keycode == K_S)
		env->keys.s = 1;
	if (keycode == K_D)
		env->keys.d = 1;
	return (0);
}

int	ft_release(int keycode, t_mlx *env)
{
	if (keycode == K_RIGHT)
		env->keys.right = 0;
	if (keycode == K_LEFT)
		env->keys.left = 0;
	if (keycode == K_W)
		env->keys.w = 0;
	if (keycode == K_A)
		env->keys.a = 0;
	if (keycode == K_S)
		env->keys.s = 0;
	if (keycode == K_D)
		env->keys.d = 0;
	return (0);
}

void	rotate(t_mlx *env)
{
	if (env->keys.left)
		rot_vec(env->map->c_dir, M_PI / 32, env->map->c_dir);
	else if (env->keys.right)
		rot_vec(env->map->c_dir, -M_PI / 32, env->map->c_dir);
}

void	move(t_mlx *env)
{
	double	tmp[2];

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
