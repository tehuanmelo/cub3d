/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:44:27 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/07/23 18:59:34 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "./mlx/mlx.h"
#include "./libft/libft.h"
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

#define PI 3.14159265
#define TWO_PI 6.28318530
#define TILE_SIZE 64
#define FOV_ANGLE 60 * (PI / 180)
#define MINI_MAP_SCALE 1

#define WALK_SPEED 1
#define TURN_SPEED 1 * (PI / 180)

#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define BLACK 0x000000

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
    KEY_ESC = 53,
    KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_UP = 126,
	KEY_DOWN = 125,
};

typedef enum s_bool
{
    false,
    true,
    hello
} t_bool;

typedef struct s_ray
{
    float ray_angle;
    float wall_hit_x;
    float wall_hit_y;
    float distance;
    t_bool was_hit_vertical;
    t_bool is_ray_facing_up; 
    t_bool is_ray_facing_down; 
    t_bool is_ray_facing_right; 
    t_bool is_ray_facing_left; 
    int wall_hit_content;
} t_ray;

typedef struct s_player 
{
    float x;
    float y;
    float width;
    float height;
    int walk_direction;
    int turn_direction;
    float rotation_angle;
} t_player;

typedef struct s_buffer {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_buffer;

typedef struct s_data
{
    void* mlx_ptr;
    void* mlx_win;
    int window_width;
    int window_height;
    int map_num_rows;
    int map_num_cols;
    int is_game_running;
    int num_rays;
    char **map;
    int floor_color;
    int cealing_color;
    t_player player;
    t_buffer buffer;
    t_ray *rays;
} t_data;

int map[12][20] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

#endif