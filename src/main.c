/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:15:23 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/08/06 20:46:56 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*init_mlx_window(t_mlx *env, char *title)
{
	void	*mlx;
	int		i;

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
	init_map(env);
	return (mlx);
}

int	exit_mlx(t_mlx *env)
{
	int	i;

	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->window)
		mlx_destroy_window(env->mlx, env->window);
	i = -1;
	while (env->map->layout && ++i < env->map->m_x)
		free(env->map->layout[i]);
	if (!env->map->layout)
		free(env->map->layout);
	i = -1;
	while (++i < 4)
		if (env->map->textures[i])
			mlx_destroy_image(env->mlx, env->map->textures[i]);
	if (env->mlx)
		free(env->mlx);
	exit(0);
}

int	main(int ac, char **av)
{
	t_mlx	env;
	t_map	map;

	if (ac != 2)
		return (ft_error("cub3d", "require config file", -1, NULL));
	env.map = &map;
	init_mlx_window(&env, "cub3d");
	if (!env.mlx)
		return (-1);
	if (parse_input(&env, av[1]))
		return (exit_mlx(&env));
	convert_map_to_vecs(&map);
	mlx_loop_hook(env.mlx, frame, &env);
	mlx_hook(env.window, 2, 1L << 0, ft_press, &env);
	mlx_hook(env.window, 3, 1L << 1, ft_release, &env);
	mlx_hook(env.window, ON_DESTROY, 0, exit_mlx, &env);
	mlx_loop(env.mlx);
	exit_mlx(&env);
	return (0);
}
