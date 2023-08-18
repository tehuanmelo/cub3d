/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:44:27 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/15 16:46:43 by tehuanmelo       ###   ########.fr       */
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

// graphics.c
int initialize_window(t_data *data);
void clear_color_buffer(t_data *data, int color);
void render_color_buffer(t_data *data);
void init_buffer_image(t_data *data);

// draw.c
void draw_pixel(t_data *data, int x, int y, int color);
void draw_rect (t_data *data, int x, int y, int width, int height, int color);
void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color);

// map.c
void render_map(t_data *data);
char **get_map(void);
int get_map_rows(char **map);
bool is_wall_at(t_data *data, float x, float y);
bool is_inside_map(t_data *data, float x, float y);

// my_mlx.c
int my_mlx_pixel_get(t_image *img, int x, int y);
void my_mlx_pixel_put(t_image *img, int x, int y, int color);
t_image create_image(t_data *data, char *image_path);

// rays.c
float clean_angle(float angle);
float get_hit_distance(float x0, float y0, float x1, float y1);
void cast_ray(t_data *data, float ray_angle, int ray_id);
void cast_all_rays(t_data *data);
void render_ray(t_data *data);

// player.c
void get_player_position(t_data *data);
void move_player(t_data *data);
void render_player(t_data *data);

//input.c
int key_pressed(int keycode, t_data *data);
int key_released(int keycode, t_data *data);

// walls.c
t_image *get_textures(t_data *data);
void render_walls(t_data *data);

// release.c
int release_resources(t_data *data);


#endif