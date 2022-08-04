#include "cub3d.h"


void draw_line(t_mlx *env, int *start, int *end, int color)
{
    double delta[2];
    int pixels;
    double pixelX;
    double pixelY;
    
    delta[1] = end[1] - start[1];
    delta[0] = end[0] - start[0];
    pixels = sqrt((delta[0] * delta[0]) + (delta[1] * delta[1]));
    pixelX = start[0];
    pixelY = start[1];
    delta[0] /= pixels;
    delta[1] /= pixels;
    while (pixels)
    {
        set_pixel(env, pixelX, pixelY, color);
        pixelX += delta[0];
        pixelY += delta[1];
        --pixels;
    }
}

void draw_circle(t_mlx *env, int *pos, int r, int color)
{
    int i;
    int j;
    
    i = - 1 - r;
    while (++i < r)
    {
        j = - 1 - r;
        while (++j < r)
            if (sqrt(i * i + j * j) < r)
                set_pixel(env, pos[0] + i, pos[1] + j, color);
    }
}

void draw_circumf(t_mlx *env, int *pos, int r, int color)
{
    int i;
    int j;
    double out;
    
    i = - 1 - r;
    while (++i < r)
    {
        j = - 1 - r;
        while (++j < r)
        {
            out = sqrt(i * i + j * j);
            if (out < r && out > r - r/10)
                set_pixel(env, pos[0] + i, pos[1] + j, color);
        }
    }
}

void draw_square(t_mlx *env, int *pos, int size, int color)
{
    int start[2];

    start[1] = ft_max(0, pos[1] - size / 2) - 1;
    while (++start[1] < HEIGHT && start[1] < pos[1] + size/2)
    {
        start[0] = ft_max(0, pos[0] - size / 2) - 1;
        while (++start[0] < WIDTH && start[0] < pos[0] + size / 2)
            set_pixel(env, start[0], start[1], color);  
    }
}

// void draw_map_axis(t_mlx *env, int *pos, int size)
// {
//     int v[4][2];

//     V[0][0] = size * cos();
//     V[0][1] = size * sin();

//     V[1][0] = ;
//     V[1][1] = ;
    
//     V[2][0] = ;
//     V[2][1] = ;
    
//     V[3][0] = ;
//     V[3][1] = ;

// }
void draw_rest(t_mlx *env, int x, int y, int size)
{
    int pos[2][2];

    pos[0][0] = x;
    pos[0][1] = y;
    draw_square(env, pos[0], size / 20, encode_rgb(127,127,127));
    pos[1][0] = x - cos(get_abs_angle(env->map->c_dir)) * size; 
    pos[1][1] = y + sin(get_abs_angle(env->map->c_dir)) * size; 
    draw_line(env, pos[0], pos[1], encode_rgb(255,0,127));
    pos[1][0] = x + cos(get_abs_angle(env->map->c_dir)) * size; 
    pos[1][1] = y - sin(get_abs_angle(env->map->c_dir)) * size; 
    draw_line(env, pos[0], pos[1], encode_rgb(127,0,127));
    pos[1][0] = x + cos(get_ord_angle(env->map->c_dir)) * size; 
    pos[1][1] = y - sin(get_ord_angle(env->map->c_dir)) * size; 
    draw_line(env, pos[0], pos[1], encode_rgb(0,255,127));
    pos[1][0] = x - cos(get_ord_angle(env->map->c_dir)) * size; 
    pos[1][1] = y + sin(get_ord_angle(env->map->c_dir)) * size; 
    draw_line(env, pos[0], pos[1], encode_rgb(0,127,127));
    draw_circumf(env, pos[0], size, encode_rgb(0,0,0));

}

void draw_map_circle(t_mlx *env, int x, int y, int size)
{
    int     pos[2][2];
    double  tmp[2][2];
    double  v[2][2];
    int     i;

    pos[0][0] = x;
    pos[0][1] = y;
    i = -1;
    draw_circle(env, pos[0], size, encode_rgb(250,255,255));
    while (++i < env->map->n_walls)
    {
        sub_vec(env->map->c_pos, env->map->walls[i][0], tmp[0]);
        sub_vec(env->map->c_pos, env->map->walls[i][1], tmp[1]);
        v[0][0] = hypot(tmp[0][0], tmp[0][1]) * size / 10;
        v[0][1] = get_abs_angle(tmp[0]) - get_ord_angle(env->map->c_dir);
        v[1][0] = hypot(tmp[1][0], tmp[1][1]) * size / 10;
        v[1][1] = get_abs_angle(tmp[1]) - get_ord_angle(env->map->c_dir);
        if (v[0][0] < size || v[1][0] < size)
        {
            pos[0][0] = x + ft_min_d(v[0][0], size - 2) * cos(v[0][1]);
            pos[0][1] = y + ft_min_d(v[0][0], size - 2) * sin(v[0][1]);
            pos[1][0] = x + ft_min_d(v[1][0], size - 2) * cos(v[1][1]);
            pos[1][1] = y + ft_min_d(v[1][0], size - 2) * sin(v[1][1]);
            draw_line(env, pos[0], pos[1], encode_rgb(0,0,0));
        }
    }
    draw_rest(env, x, y, size);

}

void draw_map_rect(t_mlx *env, int x, int y, int size)
{   
    int i;
    double tmp[2][2];
    int p[2][2];
    i = -1;

    p[0][0] = x; 
    p[0][1] = y; 
    draw_square(env, p[0], size, encode_rgb(0,0,0));
    while (++i < env->map->n_walls)
    {
        sub_vec(env->map->c_pos, env->map->walls[i][0], tmp[0]);
        sub_vec(env->map->c_pos, env->map->walls[i][1], tmp[1]);
        scale_vec_by(tmp[0], size/10, tmp[0]);
        scale_vec_by(tmp[1], size/10, tmp[1]);
        p[0][0] = x + tmp[0][0];
        p[0][1] = y - tmp[0][1];
        p[1][0] = x + tmp[1][0];
        p[1][1] = y - tmp[1][1];
        draw_line(env, p[0], p[1], encode_rgb(150,100,20));
    }
    p[0][0] = x; 
    p[0][1] = y; 
    draw_square(env, p[0], size / 20, encode_rgb(150,50,50));
    p[1][0] = x + cos(get_abs_angle(env->map->c_dir)) * 20; 
    p[1][1] = y - sin(get_abs_angle(env->map->c_dir)) * 20; 
    draw_line(env, p[0], p[1], encode_rgb(200,200,200));
}