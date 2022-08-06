/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:13:34 by gmehdevi          #+#    #+#             */
/*   Updated: 2022/06/30 14:04:12 by gmehdevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include <complex.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <mlx_int.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1000
# define HEIGHT 1000
# define K_ESCAPE 53
# define N_WALLS 10000
// linux
# define K_LEFT 65361
# define K_RIGHT 65363
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
// # define K_W				13
// # define K_A				0
// # define K_S				1
// # define K_D				2
// # define K_LEFT				123
// # define K_RIGHT			124
# define K_NUM_MULT 67
# define K_NUM_DIV 75
# define K_NUM_PLUS 69
# define K_NUM_MINUS 78
# define K_NUM_ENTER 76
# define K_NUM_0 82
# define K_UP 126
# define K_DOWN 125
# define K_L 37
# define LEFT 1
# define RIGHT 2
# define MIDDLE 3
# define SCROLLU 4
# define SCROLLD 5
# define ON_DESTROY 17
# define K_NUM_7 89
# define K_NUM_9 92
# define K_NUM_4 86
# define K_NUM_6 88
# define K_NUM_1 83
# define K_NUM_3 85
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

typedef struct s_K_data
{
	int			left;
	int			right;
	int			up;
	int			down;
	int			w;
	int			a;
	int			s;
	int			d;
	int			escape;
}				t_K_data;

typedef struct s_map
{
	int			**layout;
	double		walls[N_WALLS][2][2];
	double		fov;
	double		far;
	int			n_walls;
	int			m_x;
	int			m_y;
	int			t_w;
	int			t_h;
	t_img		*textures[4];
	int			tex_error;
	int			floor;
	int			ceil;
	double		c_pos[2];
	double		c_dir[2];
}				t_map;

typedef struct s_mlx
{
	void		*window;
	void		*img;
	char		*addr;
	int			endian;
	int			size_line;
	int			bits_per_pixel;
	t_K_data	keys;
	void		*mlx;
	t_map		*map;

}				t_mlx;

//input
void			rotate(t_mlx *env);
void			move(t_mlx *env);
int				ft_press(int keycode, t_mlx *env);
int				ft_release(int keycode, t_mlx *env);

//mlx
void			init_keys(t_K_data *keys);
int				exit_mlx(t_mlx *env);
int				frame(t_mlx *env);
int				encode_rgb(int red, int green, int blue);
void			set_pixel(t_mlx *env, int w_x, int w_y, int color);
void			init_map(t_mlx *env);

//parsing
void			convert_map_to_vecs(t_map *map);
void			set_pixel(t_mlx *env, int w_x, int w_y, int color);
int				parse_input(t_mlx *env, char *config);
int				det_cardinals(double wall[2][2]);
int				get_color(char *line);
t_img			*open_tex(t_mlx *env, char *path);
int				get_map(t_map *map, char *file);
int				get_camdir_pos(t_map *map, char card, int i, int j);
int				is_valid_map_get_sizes(t_map *map, char *file);
int				search(t_map *map, int **vis, int x, int y);
int				break_free(t_map *map);
int				get_textures_colors(t_mlx *env, int fd, int count);
char			**map_makerect(t_map *map, char *file);
void			init_layout(t_map *map);
int				parse_input(t_mlx *env, char *config);

//render
void			draw_col_tex(t_mlx *env, int x, int idx, double *dists);
void			draw_map_rect(t_mlx *env, int x, int y, int size);
void			draw_map_circle(t_mlx *env, int x, int y, int size);
void			draw_circle(t_mlx *env, int *pos, int r, int color);
void			draw_square(t_mlx *env, int *pos, int size, int color);
void			map_to_screen(t_mlx *env, double a, double b, int *res);
int				encode_rgb(int red, int green, int blue);
void			draw_closest_wall(t_mlx *env, double *ray, int x);
void			cast_rays(t_mlx *env);
void			render_background(t_mlx *env);
void			draw_map(t_mlx *env, int x, int y, int size);

//math
double			get_ord_angle(double *v1);
double			vec_cross(double *v1, double *v2);
void			rot_vec(double *v, double a, double *res);
void			sub_vec(double *v1, double *v2, double *res);
void			add_vec(double *v1, double *v2, double *res);
void			vec_mult(double *v, double c, double *res);
double			dot(double *v1, double *v2);
double			get_angle(double *v1, double *v2);
void			scale_vec_to(double *v, double c, double *res);
double			get_abs_angle(double *v1);
void			inter_dist(double p[2][2], double v[2][2], double *dist,
					double *wall_x);
int				collide(t_map *map, double size);
void			vec_equal(double *v1, double *v2);

#endif