/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:44:27 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/10 15:44:17 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "./mlx/mlx.h"
#include "./libft/libft.h"
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <fcntl.h>
#include <stdbool.h>

#define PI 3.14159265
#define TWO_PI 6.28318530
#define TILE_SIZE 64
#define FOV_ANGLE 60 * (PI / 180)
#define MINI_MAP_SCALE 0.25

#define WALK_SPEED 8
#define TURN_SPEED 6 * (PI / 180)

#define WHITE 0xFFFFFF
#define SHADE 0xDDDDDD
#define RED 0xFF0000
#define BLACK 0x000000
#define GREEN 0x00EE00
#define SKY 0x0ADD8E6
#define BROWN 0x964B00
#define DARK_GREY 0x404040
#define MEDIUN_GREY 0xA0A0A0
#define LIGHT_GREY 0x808080

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
    KEY_A = 0,
    KEY_W = 13,
    KEY_S = 1,
    KEY_D = 2
    
};

typedef struct s_ray
{
    float ray_angle;
    float wall_hit_x;
    float wall_hit_y;
    float distance;
    bool was_hit_vertical;
    bool is_ray_facing_up; 
    bool is_ray_facing_down; 
    bool is_ray_facing_right; 
    bool is_ray_facing_left; 
    int wall_hit_content;
} t_ray;

typedef struct s_player 
{
    float x;
    float y;
    float width;
    float height;
    int walk_direction;
    int side_direction;
    int turn_direction;
    float rotation_angle;
} t_player;

typedef struct s_image {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int width;
    int height;
} t_image;

typedef struct s_data
{
    void* mlx_ptr;
    void* mlx_win;
    int window_width;
    int window_height;
    int map_num_rows;
    int map_num_cols;
    int num_rays;
    int floor_color;
    int cealing_color;
    bool is_game_running;
    t_player player;
    t_image buffer_image;
    t_image *textures;
    t_ray *rays;
    char **map;
    int *color_buffer;
} t_data;

#endif