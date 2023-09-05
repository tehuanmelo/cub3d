/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:44:27 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/09/05 15:48:32 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

# define PI 3.14159265
# define TWO_PI 6.28318530
# define TILE_SIZE 64
# define FOV_ANGLE 1.0471975500000001 // is the result of 60 * (PI / 180)
# define MINI_MAP_SCALE 0.15
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 800
# define PLAYER_WIDTH 3
# define PLAYER_HEIGHT 3

# define WALK_SPEED 8
# define TURN_SPEED 4

# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define BLACK 0x000000
# define DARK_GREY 0x404040
# define LIGHT_GREY 0x808080

enum
{
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

typedef struct s_rect
{
	int				x;
	int				y;
	int				width;
	int				height;
	int				color;
}					t_rect;

typedef struct s_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				delta_x;
	int				delta_y;
	int				side_step;
	float			current_x;
	float			current_y;
	float			inc_x;
	float			inc_y;
	int				color;
}					t_line;

typedef struct s_wall
{
	float			projected_wall_dist;
	float			corrected_ray_distance;
	int				projected_wall_height;
	int				top_pixel;
	int				bottom_pixel;
	int				texel_color;
	int				x_texture_offset;
	int				y_texture_offset;
	int				distance_from_top;
	int				orientation;
}					t_wall;

typedef struct s_colision
{
	float			x_intercept;
	float			y_intercept;
	float			next_x_intercept;
	float			next_y_intercept;
	float			x_step;
	float			y_step;
	float			check_x;
	float			check_y;
	int				found_wall_hit;
	float			wall_hit_x;
	float			wall_hit_y;
	float			hit_distance;
	bool			is_horizontal;
}					t_colision;

typedef struct s_ray_direction
{
	bool			is_ray_facing_up;
	bool			is_ray_facing_down;
	bool			is_ray_facing_right;
	bool			is_ray_facing_left;
}					t_ray_direction;

typedef struct s_ray
{
	float			ray_angle;
	float			wall_hit_x;
	float			wall_hit_y;
	float			distance;
	bool			was_hit_vertical;
	t_ray_direction	direction;
}					t_ray;

typedef struct s_player
{
	float			x;
	float			y;
	int				walk_direction;
	int				side_direction;
	int				turn_direction;
	float			rotation_angle;
}					t_player;

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
	float			mini_map_scale;
	int				map_num_rows;
	int				map_num_cols;
	int				num_rays;
	int				floor_color;
	int				cealing_color;
	bool			is_game_running;
	t_player		player;
	t_image			buffer_image;
	t_image			*textures;
	t_image			texture;
	t_ray			*rays;
	char			**map;
	int				*color_buffer;
}					t_data;

// graphics.c
int					initialize_window(t_data *data);
void				clear_color_buffer(t_data *data, int color);
void				render_color_buffer(t_data *data);
void				init_buffer_image(t_data *data);

// draw.c
void				draw_pixel(t_data *data, int x, int y, int color);
void				draw_rect(t_data *data, t_rect rect);
void				draw_line(t_data *data, t_line line);

// map.c
void				render_map(t_data *data);
bool				is_wall_at(t_data *data, float x, float y);
bool				is_inside_map(t_data *data, float x, float y);
float				map_scale_factor(t_data *data);

// my_mlx.c
int					my_mlx_pixel_get(t_image *img, int x, int y);
void				my_mlx_pixel_put(t_image *img, int x, int y, int color);
t_image				create_image(t_data *data, char *image_path);

// rays.c
float				clean_angle(float angle);
float				get_hit_distance(float x0, float y0, float x1, float y1);
void				cast_ray(t_data *data, float ray_angle, int ray_id);
void				cast_all_rays(t_data *data);
void				render_ray(t_data *data);
t_ray_direction		get_ray_direction(float ray_angle);
void				find_colision(t_data *data, t_colision *colision,
						bool direction);
void				init_colision(t_colision *colision, bool is_horizontal);
t_colision			get_horizontal_colision(t_data *data, 
						t_ray_direction ray_direction, float ray_angle);
t_colision			get_vertical_colision(t_data *data,
						t_ray_direction ray_direction, float ray_angle);

// player.c
void				get_player_position(t_data *data);
void				move_player(t_data *data);
void				render_player(t_data *data);
void				get_rotation_angle(t_data *data, int i, int j);

//input.c
int					key_pressed(int keycode, t_data *data);
int					key_released(int keycode, t_data *data);
int					mouse_event(int x, int y, t_data *data);

// walls.c
void				draw_cealing(t_data *data, t_wall wall, int x);
void				draw_floor(t_data *data, t_wall wall, int x);
void				init_wall(t_data *data, t_wall *wall, int x);
void				draw_wall(t_data *data, t_wall wall, int x);
void				render_walls(t_data *data);

// release.c
void				parse_release(t_data *data);
int					release_resources(t_data *data);

// check.c
int					charcheck(t_data *data);
int					issurrounded(t_data *data);
int					floodfill(t_data *data);

// info.c
int					parsedata(t_data *data, t_list *info);

// parse.c
int					parse(t_data *data, char *filename);

// utils.c
char				**make2d(int rows, int cols);
void				free2d(char **strs);
t_list				*readlines(int fd);
int					isemptyline(char *str);
void				stopcorner(t_data *data, char **checked);

// putinfo.c
int					putdata(t_data *data, char *strinfo[6]);
void				removestart(char *str);

#endif
