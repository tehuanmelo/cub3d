/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:47:02 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/07/24 14:32:10 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int initialize_window(t_data *data) {
    data->mlx_ptr = mlx_init();
    data->mlx_win = mlx_new_window(data->mlx_ptr, data->window_width, data->window_height, "Cub3d");
    if (!data->mlx_ptr || !data->mlx_win)
    {
        perror("Could not initialize the window");
        return FALSE;
    }
    return TRUE;
}

int exit_game(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    data->mlx_ptr = NULL;
    exit(EXIT_SUCCESS);
}

int key_pressed(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
        data->is_game_running = FALSE;
    else if (keycode == KEY_UP)
        data->player.walk_direction = 1;
    else if (keycode == KEY_DOWN)
        data->player.walk_direction = -1;
    else if (keycode == KEY_RIGHT)
        data->player.turn_direction = 1;
    else if (keycode == KEY_LEFT)
        data->player.turn_direction = -1;
    return EXIT_SUCCESS;
}

int key_released(int keycode, t_data *data)
{
    if (keycode == KEY_UP)
        data->player.walk_direction = 0;
    else if (keycode == KEY_DOWN)
        data->player.walk_direction = 0;
    else if (keycode == KEY_RIGHT)
        data->player.turn_direction = 0;
    else if (keycode == KEY_LEFT)
        data->player.turn_direction = 0;
    return EXIT_SUCCESS;
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
     char *dst;
    dst = data->buffer.addr + (y * data->buffer.line_length + x * (data->buffer.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_rectangle(t_data *data, int x, int y, int width, int height, int color)
{
    int end_x;
    int end_y;
    int starting_x;

    end_x = x + width;
    end_y = y + height;
    starting_x = x;

    while (y < end_y)
    {
        x = starting_x;
        while (x < end_x)
        {
            my_mlx_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(data, x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

t_ray *init_rays(t_data *data)
{
    t_ray *rays;

    rays = malloc(data->num_rays * sizeof(t_ray));
    if (!rays)
        return NULL;
    return rays;
}

void setup(t_data *data)
{
    data->mlx_ptr = NULL;
    data->mlx_win = NULL;
    data->map_num_rows = sizeof(map) / sizeof(map[0]);
    data->map_num_cols = sizeof(map[0]) / sizeof(map[0][0]);
    data->window_width = data->map_num_cols * TILE_SIZE;
    data->window_height = data->map_num_rows * TILE_SIZE;
    data->is_game_running = FALSE;
    data->num_rays = data->window_width;
    data->player.x = data->window_width / 2;
    data->player.y = data->window_height / 2;
    data->player.width = 10;
    data->player.height = 10;
    data->player.walk_direction = 0;
    data->player.turn_direction = 0; 
    data->player.rotation_angle = PI / 2; // it will be setted by the map, in this case it is 90 degrees radians facing South
    data->rays = init_rays(data);
}

void init_buffer(t_data *data)
{
    data->buffer.img = mlx_new_image(data->mlx_ptr, data->window_width, data->window_height);
    data->buffer.addr = mlx_get_data_addr(data->buffer.img, &data->buffer.bits_per_pixel, &data->buffer.line_length, &data->buffer.endian);
}

int is_wall_at(t_data *data, float x, float y)
{
    int map_grid_x;
    int map_grid_y;
    
    // if x and y coordinates are out of boundaries is wall return true and do not move the player
    if ((x < 0 || x > data->window_width) || (y < 0 || y > data->window_height))
        return TRUE;
    
    // divide the coordinate by the tile size to find the position in the map array.
    // round it down to get an integer value
    map_grid_x = floor(x / TILE_SIZE);
    map_grid_y = floor(y / TILE_SIZE);
    
    return map[map_grid_y][map_grid_x] == 1;
}

void move_player(t_data *data)
{
    float move_step;
    float new_player_x;
    float new_player_y;

    new_player_x = data->player.x;
    new_player_y = data->player.y;
    
    // the distance we want to move, 1 forward or -1 backward from walk_direction
    // WALK_SPEED is the number of pixels the player will move
    move_step = data->player.walk_direction * WALK_SPEED;
    
    // increment or decrement the player angle based on the turn_direction 
    // times TURN_SPEED. How many angles we want to move
    data->player.rotation_angle += data->player.turn_direction * TURN_SPEED;
    
    // Basic trigonometry to find the new coordinates
    // move step being the hypotenuse, new_player_x adjacent, new_player_y oposite
    new_player_x = data->player.x + cos(data->player.rotation_angle) * move_step;
    new_player_y = data->player.y + sin(data->player.rotation_angle) * move_step;
    
    // check if there is a wall in the new coordinates
    if (!is_wall_at(data, new_player_x, new_player_y))
    {
        data->player.x = new_player_x;
        data->player.y = new_player_y;
    }

}


void render_player(t_data *data)
{

    draw_line(
        data,
        data->player.x * MINI_MAP_SCALE,
        data->player.y * MINI_MAP_SCALE,
        (data->player.x + cos(data->player.rotation_angle) * 40) * MINI_MAP_SCALE,
        (data->player.y + sin(data->player.rotation_angle) * 40) * MINI_MAP_SCALE,
        WHITE
    );

}

// clean angle returns a positive angle e.g -3 % 360 = 357 degrees
// remainder function replaces modulus to returns a float 
float clean_angle(float angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0)
        angle += TWO_PI;
    return angle;
}

float get_hit_distance(float x0, float y0, float x1, float y1)
{
    return sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0)));
}

void cast_ray(t_data *data, float ray_angle, int ray_id)
{
    // float xstep; // the deltax and deltay
    // float ystep; // the deltax and deltay
    // float xintercept; // the first intersection point
    // float yintercept; // the first intersection point
    // float next_xintercept;
    // float next_yintercept;
    // float next_yintercept_tmp;
    // float wall_horz_x_hit;
    // float wall_horz_y_hit;
    // t_bool found_horz_hit;
    // t_bool is_ray_facing_up;
    // t_bool is_ray_facing_down;
    // t_bool is_ray_facing_right;
    // t_bool is_ray_facing_left;

    // /////////////////////////////////////////////////////////////
    // //////// HORIZONTAL INSTERSECTION IMPLEMENTATION ////////////
    // /////////////////////////////////////////////////////////////
    
    // ray_angle = clean_angle(ray_angle);
    // found_horz_hit = false;
    // wall_horz_x_hit = 0;
    // wall_horz_y_hit = 0;
    
    // //check the ray direction
    // is_ray_facing_down = ray_angle < 0 && ray_angle < PI;
    // is_ray_facing_up = !is_ray_facing_down;
    // is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    // is_ray_facing_left = !is_ray_facing_right;

    // // it rounds down the y coordinate of the player, getting the first horizontal line before the player coordinate 
    // yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    // // if the ray is facing down means is the next horizontal line after the player coordinate so we add tilesize
    // if (is_ray_facing_down)
    //     yintercept += TILE_SIZE;
        
    // xintercept = data->player.x + ((yintercept - data->player.y) / tan(ray_angle));
    
    
    // ystep = TILE_SIZE;
    // if (is_ray_facing_up)
    //     ystep *= -1;
        
    // xstep = TILE_SIZE / tan(ray_angle);
    // if (is_ray_facing_left && xstep > 0)
    //     xstep *= -1;
    // if (is_ray_facing_right && xstep < 0)
    //     xstep *= -1;

    // next_xintercept = xintercept;
    // next_yintercept = yintercept;

    // while ((next_xintercept >= 0 && next_xintercept <= data->window_width) && (next_yintercept >= 0 && next_yintercept <= data->window_height))
    // {
    //     next_yintercept_tmp = next_yintercept;
    //     if (is_ray_facing_up)
    //         next_yintercept_tmp--;
    //     if(is_wall_at(data, next_xintercept, next_yintercept_tmp))
    //     {
    //         wall_horz_x_hit = next_xintercept;
    //         wall_horz_y_hit = next_yintercept;
    //         found_horz_hit = true;
    //         break;
    //     }
    //     else 
    //     {
    //         next_xintercept += xstep;
    //         next_yintercept += ystep;
    //     }
    // }
    
    // float horz_hit_distance;
    // if (found_horz_hit)
    // {
    //     horz_hit_distance = get_hit_distance(data->player.x, data->player.y, wall_horz_x_hit, wall_horz_y_hit);
    //     data->rays[ray_id].distance = horz_hit_distance;
    //     data->rays[ray_id].wall_hit_x = wall_horz_x_hit;
    //     data->rays[ray_id].wall_hit_y = wall_horz_y_hit;
    //     data->rays[ray_id].was_hit_vertical = FALSE;
    // }
    //     data->rays[ray_id].ray_angle = ray_angle;
    //     data->rays[ray_id].is_ray_facing_up = is_ray_facing_up;
    //     data->rays[ray_id].is_ray_facing_down = is_ray_facing_down;
    //     data->rays[ray_id].is_ray_facing_right = is_ray_facing_right;
    //     data->rays[ray_id].is_ray_facing_left = is_ray_facing_left;

     ray_angle = clean_angle(ray_angle);
    
    int isRayFacingDown = ray_angle > 0 && ray_angle < PI;
    int isRayFacingUp = !isRayFacingDown;

    int isRayFacingRight = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;
    
    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = FALSE;
    float horzWallHitX = 0;
    float horzWallHitY = 0;
    int horzWallContent = 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    yintercept += isRayFacingDown ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = data->player.x + (yintercept - data->player.y) / tan(ray_angle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = TILE_SIZE / tan(ray_angle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= data->window_width && nextHorzTouchY >= 0 && nextHorzTouchY <= data->window_height) {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
        
        if (is_wall_at(data, xToCheck, yToCheck)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = TRUE;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }

    }

    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = FALSE;
    float vertWallHitX = 0;
    float vertWallHitY = 0;
    int vertWallContent = 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
    xintercept += isRayFacingRight ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = data->player.y + (xintercept - data->player.x) * tan(ray_angle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = TILE_SIZE * tan(ray_angle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= data->window_width && nextVertTouchY >= 0 && nextVertTouchY <= data->window_height) {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;
        
        if (is_wall_at(data, xToCheck, yToCheck)) {
            // found a wall hit
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = TRUE;
            break;
        } else {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

float horzHitDistance = foundHorzWallHit
        ? get_hit_distance(data->player.x, data->player.y, horzWallHitX, horzWallHitY)
        : INT_MAX;
    float vertHitDistance = foundVertWallHit
        ? get_hit_distance(data->player.x, data->player.y, vertWallHitX, vertWallHitY)
        : INT_MAX;

    if (vertHitDistance < horzHitDistance) {
        data->rays[ray_id].distance = vertHitDistance;
        data->rays[ray_id].wall_hit_x = vertWallHitX;
        data->rays[ray_id].wall_hit_y = vertWallHitY;
        data->rays[ray_id].wall_hit_content = vertWallContent;
        data->rays[ray_id].was_hit_vertical = TRUE;
    } else {
        data->rays[ray_id].distance = horzHitDistance;
        data->rays[ray_id].wall_hit_x = horzWallHitX;
        data->rays[ray_id].wall_hit_y = horzWallHitY;
        data->rays[ray_id].wall_hit_content = horzWallContent;
        data->rays[ray_id].was_hit_vertical = FALSE;
    }
    data->rays[ray_id].ray_angle = ray_angle;
    data->rays[ray_id].is_ray_facing_down = isRayFacingDown;
    data->rays[ray_id].is_ray_facing_up = isRayFacingUp;
    data->rays[ray_id].is_ray_facing_left = isRayFacingLeft;
    data->rays[ray_id].is_ray_facing_right = isRayFacingRight;
    
}

void cast_all_rays(t_data *data)
{
    float ray_angle;
    int i;

    // we start casting the rays from left to right, the first ray is the actual player angle minus the half of field of view
    ray_angle = data->player.rotation_angle - (FOV_ANGLE / 2);
    i = 0;
    while (i < data->num_rays)
    {
        cast_ray(data, ray_angle, i);
        // update the ray_angle to the next angle, FOV divided by the number of rays
        // if FOV is 60 and we need 800 rays. we increment the angle in 0.075
        ray_angle += FOV_ANGLE / data->num_rays;
        i++;
    }
}

void render_ray(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_rays)
    {
        draw_line(
            data, 
            data->player.x, 
            data->player.y, 
            data->rays[i].wall_hit_x, 
            data->rays[i].wall_hit_y, 
            RED);
        i++;
    }
}

void render_map(t_data *data)
{
    int tile_x;
    int tile_y;
    int tile_color;
    int i;
    int j;

    i = 0;
    while (i < data->map_num_rows)
    {
        j = 0;
        while (j < data->map_num_cols) 
        {
            tile_x = j * TILE_SIZE;
            tile_y = i * TILE_SIZE;
            if (map[i][j] == 1)
                tile_color = WHITE;
            else
                tile_color = BLACK;
            draw_rectangle(data, tile_x * MINI_MAP_SCALE, tile_y * MINI_MAP_SCALE, TILE_SIZE * MINI_MAP_SCALE, TILE_SIZE * MINI_MAP_SCALE, tile_color);
            j++;  
        }
        i++;
    }
}

void update(t_data *data) 
{
    move_player(data);
    cast_all_rays(data);
}

void render(t_data *data)
{
    mlx_clear_window(data->mlx_ptr, data->mlx_win);
    init_buffer(data);
    render_map(data);
    render_ray(data);
    render_player(data); 
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->buffer.img, 0, 0);
    if (data->buffer.img)
        mlx_destroy_image(data->mlx_ptr, data->buffer.img);
}

int game_loop(t_data *data)
{
    if (!data->is_game_running)
        exit_game(data);
    update(data);
    render(data);
    return TRUE;
}

int main() 
{
    t_data data;
    
    setup(&data);

    data.is_game_running = initialize_window(&data);
     
    if (data.is_game_running) 
    {
        mlx_loop_hook(data.mlx_ptr, game_loop, &data);
        mlx_hook(data.mlx_win, 2, 1L << 0, key_pressed, &data);
	    mlx_hook(data.mlx_win, 3, 1L << 0, key_released, &data);
        mlx_hook(data.mlx_win, ON_DESTROY, 1L << 17, exit_game, &data);
        mlx_loop(data.mlx_ptr);
    }
    
    exit_game(&data);

    
        
    return 0;
}