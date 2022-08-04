/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:15:23 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/06/29 17:45:16 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include  <stdio.h>

void	*init_mlx_window(t_mlx *env, char *title)
{
	void	*mlx;
	int	i;

	mlx = mlx_init();
	if (!mlx)
		return (NULL);
	env->window = mlx_new_window(mlx, WIDTH, HEIGHT, title);
	if (!env->window)
		return (NULL);
	env->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel,
			&env->size_line, &env->endian);
	if (!env->addr)
		return (NULL);
	env->mlx = mlx;
	init_keys(&env->keys);
	i = -1;
	while (++i < 4)
		env->map->textures[i] = NULL;
	env->map->tex_error = 0;
	env->map->m_y = 0;
	env->map->m_x = 0;
	env->map->fov = M_PI_4;
	env->map->far = 1000;
	return (mlx);
}

int	exit_mlx(t_mlx *env)
{
	int	i;

	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->window)
		mlx_destroy_window(env->mlx, env->window);
	if (env->img)
	i = -1;
	while (++i < env->map->m_x)
		free(env->map->layout[i]);
	free(env->map->layout);
	i = -1;
	while (++i < 4)
		mlx_destroy_image(env->mlx, env->map->textures[i]);
	free(env->mlx);
	exit(0);
}

void print_layout(t_map *map)
{
	for (int i = 0; i < map->m_y; i++)
	{
		for (int j = 0; j < map->m_x; j++)
			ft_printf("%d", map->layout[j][i]);
		ft_printf("\n");
	}
}
// mlx_hook(env.window, 4, 1L << 2, hook_mouse, &env);
// mlx_hook(env.window, 6, 1L << 6, hook_mouse_move, &env);
int	main(int ac, char **av)
{	
	t_mlx				env;
	t_render			render;
	t_map				map;

	if (ac != 2)
		return (ft_error("cub3d", "require config file", -1));
	env.map = &map;
	init_mlx_window(&env, "cub3d");
	if (!env.mlx)
		return (-1);
	if (parse_input(&env, av[1]))
		return (exit_mlx(&env));
	convert_map_to_vecs(&map);
	init_render(&render, env.mlx, &env);
	mlx_loop_hook(env.mlx, frame, &env);
	mlx_hook(env.window, 2, 1L << 0, ft_press, &env);
	mlx_hook(env.window, 3, 1L << 1, ft_release, &env);
	mlx_hook(env.window, ON_DESTROY, 0, exit_mlx, &env);
	mlx_loop(env.mlx);
	exit_mlx(&env);
	return (0);
}
