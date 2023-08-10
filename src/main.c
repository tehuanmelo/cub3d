
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tehuanmelo <tehuanmelo@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:47:02 by tehuanmelo        #+#    #+#             */
/*   Updated: 2023/08/05 13:34:52 by tehuanmelo       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int initialize_window(t_data *data) {
    data->mlx_win = mlx_new_window(data->mlx_ptr, data->window_width, data->window_height, "Cub3d");
    if (!data->mlx_ptr || !data->mlx_win)
    {
        perror("Could not initialize the window");
        return false;
    }
    return true;
}

int release_resources(t_data *data)
{
    int i;

    free(data->rays);
    free(data->color_buffer);
    i = 0;
    while (data->map[i])
        free(data->map[i++]);
    free(data->map);
    i = 0;
    while (i < 4)
        mlx_destroy_image(data->mlx_ptr, data->textures[i++].img);
    free(data->textures);
    mlx_destroy_window(data->mlx_ptr, data->mlx_win);
    data->mlx_ptr = NULL;
    exit(EXIT_SUCCESS);
}

int key_pressed(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
        data->is_game_running = false;
    else if (keycode == KEY_W || keycode == KEY_UP)
        data->player.walk_direction = 1;
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        data->player.walk_direction = -1;
    else if (keycode == KEY_A)
        data->player.side_direction = 1;
    else if (keycode == KEY_D)
        data->player.side_direction = -1;
    else if (keycode == KEY_RIGHT)
        data->player.turn_direction = 1;
    else if (keycode == KEY_LEFT)
        data->player.turn_direction = -1;
    return EXIT_SUCCESS;
}

int key_released(int keycode, t_data *data)
{
    if (keycode == KEY_W || keycode == KEY_UP)
        data->player.walk_direction = 0;
    else if (keycode == KEY_S || keycode == KEY_DOWN)
        data->player.walk_direction = 0;
    else if (keycode == KEY_A)
        data->player.side_direction = 0;
    else if (keycode == KEY_D)
        data->player.side_direction = 0;
    else if (keycode == KEY_RIGHT)
        data->player.turn_direction = 0;
    else if (keycode == KEY_LEFT)
        data->player.turn_direction = 0;
    return EXIT_SUCCESS;
}

t_image create_image(t_data *data, char *image_path)
{
    t_image img;
    img.width = 64;
    img.height = 64;
    img.img = mlx_xpm_file_to_image(data->mlx_ptr, image_path, &img.width, &img.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    return (img);
}

int my_mlx_pixel_get(t_image *img, int x, int y)
{
    int color;
    char *dst;
    
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    color = *(unsigned int *)dst;
    return color;
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
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
            my_mlx_pixel_put(&data->buffer_image, x, y, color);
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
        my_mlx_pixel_put(&data->buffer_image, x0, y0, color);

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

char **get_map()
{
    int fd = open("map/map.cub", O_RDONLY);
    char *buffer = malloc(100000 * sizeof(char));
    char character;
    int flag;
    int i = 0;

    while ((flag = read(fd, &character, 1)) > 0)
        buffer[i++] = character;
    buffer[i] = 0;
    if (flag == -1 || i == 0)
        return free(buffer), NULL;

    char **map = ft_split(buffer, '\n');
    if (map == NULL)
        return free(buffer), NULL;
    free(buffer);
    return map;
}

int get_map_rows(char **map)
{
    int rows = 0;
    while (*map++)
        rows++;
    return rows;
}

void get_player_position(t_data *data)
{
    int i;
    int j;

    i = -1;
    while (data->map[++i])
    {
        j = -1;
        while (data->map[i][++j])
        {
            if (data->map[i][j] != '0' && data->map[i][j] != '1')
            {
                if (data->map[i][j] == 'N')
                    data->player.rotation_angle = 0.75 * (2 * PI);
                else if (data->map[i][j] == 'S')
                    data->player.rotation_angle = 0.25 * (2 * PI);
                else if (data->map[i][j] == 'E')
                    data->player.rotation_angle = 2 * (2 * PI);
                else if (data->map[i][j] == 'W')
                    data->player.rotation_angle = 0.5 * (2 * PI);
                data->player.x = j * TILE_SIZE;
                data->player.y = i * TILE_SIZE;
                return;
            }
        }
    }
}

t_image *get_textures(t_data *data)
{
    t_image *textures;

    textures = malloc(sizeof(t_image) * 4);
    if (!textures)
        return NULL;
    textures[0] = create_image(data, "textures/BLUE-ROCK.xpm");
    textures[1] = create_image(data, "textures/BROWN-ROCK.xpm");
    textures[2] = create_image(data, "textures/SILVER-ROCK.xpm");
    textures[3] = create_image(data, "textures/MOSS-ROCK.xpm");

    return textures;
}

void setup(t_data *data)
{
    data->mlx_ptr = mlx_init();
    data->mlx_win = NULL;
    data->map = get_map();
    data->map_num_rows = get_map_rows(data->map);
    data->map_num_cols = ft_strlen(data->map[0]);
    data->window_width = data->map_num_cols * TILE_SIZE;
    data->window_height = data->map_num_rows * TILE_SIZE;
    data->cealing_color = DARK_GREY;
    data->floor_color = LIGHT_GREY;
    data->is_game_running = false;
    data->num_rays = data->window_width;
    data->player.width = 10;
    data->player.height = 10;
    data->player.walk_direction = 0;
    data->player.side_direction = 0;
    data->player.turn_direction = 0; 
    data->rays = malloc(data->num_rays * sizeof(t_ray));
    data->color_buffer = malloc((data->window_width * data->window_height) * sizeof(int));
    data->textures = get_textures(data);
    get_player_position(data);
}

void init_buffer_image(t_data *data)
{
    data->buffer_image.img = mlx_new_image(data->mlx_ptr, data->window_width, data->window_height);
    data->buffer_image.addr = mlx_get_data_addr(data->buffer_image.img, &data->buffer_image.bits_per_pixel, &data->buffer_image.line_length, &data->buffer_image.endian);
}

int is_wall_at(t_data *data, float x, float y)
{
    int map_grid_x;
    int map_grid_y;
    
    // if x and y coordinates are out of boundaries returns true and do not move the player
    if ((x < 0 || x >= data->window_width) || (y < 0 || y >= data->window_height))
        return true;
    
    // divide the coordinate by the tile size to find the position in the map array.
    // round it down to get an integer value
    map_grid_x = floor(x / TILE_SIZE);
    map_grid_y = floor(y / TILE_SIZE);
    
    return data->map[map_grid_y][map_grid_x] == '1';
}

void move_player(t_data *data)
{
    float move_step;
    float side_move_step;
    float side_angle;
    float new_player_x;
    float new_player_y;

    new_player_x = data->player.x;
    new_player_y = data->player.y;
    
    // the distance we want to move, 1 forward or -1 backward from walk_direction
    // WALK_SPEED is the number of pixels the player will move
    move_step = data->player.walk_direction * WALK_SPEED;
    side_move_step = data->player.side_direction * WALK_SPEED;
    
    // increment or decrement the player angle based on the turn_direction 
    // times TURN_SPEED. How many angles we want to move
    data->player.rotation_angle += data->player.turn_direction * TURN_SPEED;
    side_angle = data->player.rotation_angle - (PI / 2);
    
    // Basic trigonometry to find the new coordinates
    // move step being the hypotenuse, new_player_x adjacent, new_player_y oposite
    new_player_x += cos(data->player.rotation_angle) * move_step;
    new_player_y += sin(data->player.rotation_angle) * move_step;

    new_player_x += cos(side_angle) * side_move_step;
    new_player_y += sin(side_angle) * side_move_step;
    
    // check if there is a wall in the new coordinates
    if (!is_wall_at(data, new_player_x, new_player_y))
    {
        data->player.x = new_player_x;
        data->player.y = new_player_y;
    }

}


void render_player(t_data *data)
{

    // draw_rectangle(
    //     data, 
    //    (data->player.x - 8) * MINI_MAP_SCALE, 
    //    (data->player.y - 8) * MINI_MAP_SCALE, 
    //     4,
    //     4,
    //     RED
    //     );

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
    ray_angle = clean_angle(ray_angle);
    
    int isRayFacingUp = ray_angle > PI && ray_angle < TWO_PI;
    int isRayFacingDown = !isRayFacingUp;

    int isRayFacingRight = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;
    
    float xintercept, yintercept;
    float xstep, ystep;

    ///////////////////////////////////////////
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundHorzWallHit = false;
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
        float yToCheck = nextHorzTouchY;
        if (isRayFacingUp)
            yToCheck--;
        
        if (is_wall_at(data, xToCheck, yToCheck)) {
            // found a wall hit
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = data->map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundHorzWallHit = true;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }

    }

    ///////////////////////////////////////////
    // VERTICAL RAY-GRID INTERSECTION CODE
    ///////////////////////////////////////////
    int foundVertWallHit = false;
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
            vertWallContent = data->map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            foundVertWallHit = true;
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
        data->rays[ray_id].was_hit_vertical = true;
    } else {
        data->rays[ray_id].distance = horzHitDistance;
        data->rays[ray_id].wall_hit_x = horzWallHitX;
        data->rays[ray_id].wall_hit_y = horzWallHitY;
        data->rays[ray_id].wall_hit_content = horzWallContent;
        data->rays[ray_id].was_hit_vertical = false;
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
            data->player.x * MINI_MAP_SCALE, 
            data->player.y * MINI_MAP_SCALE, 
            data->rays[i].wall_hit_x * MINI_MAP_SCALE, 
            data->rays[i].wall_hit_y * MINI_MAP_SCALE, 
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
            if (data->map[i][j] == '1')
                tile_color = WHITE;
            else
                tile_color = BLACK;
            draw_rectangle(data, tile_x * MINI_MAP_SCALE, tile_y * MINI_MAP_SCALE, TILE_SIZE * MINI_MAP_SCALE, TILE_SIZE * MINI_MAP_SCALE, tile_color);
            j++;  
        }
        i++;
    }
}

void generate_floor_cealing(t_data *data)
{
    int i;

    i = 0;
    while (i < (data->window_width * data->window_height) / 2)
        data->color_buffer[i++] = data->cealing_color;
    i = (data->window_width * data->window_height) / 2;
    while ( i < (data->window_height * data->window_width))
        data->color_buffer[i++] = data->floor_color;
}

void generate_3d_walls(t_data *data)
{
    int x;
    int y;
    float corrected_ray_distance;
    float dist_projected_wall;
    int projected_wall_height;
    int top_pixel;
    int bottom_pixel;

    x = 0;
    while (x < data->num_rays)
    {
        dist_projected_wall = (data->window_width / 2) / (FOV_ANGLE / 2);
        // fixing the fish eye effect
        corrected_ray_distance = data->rays[x].distance * cos(data->player.rotation_angle - data->rays[x].ray_angle);
        
        projected_wall_height = (int)((TILE_SIZE / corrected_ray_distance * dist_projected_wall));
        top_pixel = (data->window_height / 2) - (projected_wall_height / 2);
        bottom_pixel = (data->window_height / 2) + (projected_wall_height / 2);
         
        if (top_pixel < 0)
            top_pixel = 0;
        if (bottom_pixel > data->window_height)
            bottom_pixel = data->window_height;
        
        int textureOffsetX;
        if (data->rays[x].was_hit_vertical)
            textureOffsetX = (int)data->rays[x].wall_hit_y % TILE_SIZE;
        else
            textureOffsetX = (int)data->rays[x].wall_hit_x % TILE_SIZE;

        // render the wall from wallTopPixel to wallBottomPixel
        y = top_pixel;
        while (y < bottom_pixel) 
        {
            int distanceFromTop = y + (projected_wall_height / 2) - (data->window_height / 2); // allows the top pixel be negative and prevent distortion
            int textureOffsetY = distanceFromTop * ((float)TILE_SIZE / projected_wall_height); // 

            // set the color of the wall based on the color from the texture
            int orientation = 0;
            if (!data->rays[x].was_hit_vertical && data->rays[x].is_ray_facing_up)
                orientation = 2;
            else if (!data->rays[x].was_hit_vertical && data->rays[x].is_ray_facing_down)
                orientation = 2;
            else if (data->rays[x].was_hit_vertical && data->rays[x].is_ray_facing_left)
                orientation = 3;
            else if (data->rays[x].was_hit_vertical && data->rays[x].is_ray_facing_right)
                orientation = 3;

            int texelColor = my_mlx_pixel_get(&data->textures[orientation], textureOffsetX, textureOffsetY);
            data->color_buffer[(data->window_width * y) + x] = texelColor;
            y++;
        }
            
        x++;
    }
}

void render_color_buffer(t_data *data)
{
    int x;
    int y;

    x = 0;
    while (x < data->window_width)
    {
        y = 0;
        while (y < data->window_height)
        {
            my_mlx_pixel_put(&data->buffer_image, x, y, data->color_buffer[(data->window_width * y) + x]);
            y++;
        }
        x++;
    }
}

void clear_color_buffer(t_data *data, int color)
{
    int i;

    i = 0;
    while (i < data->window_width * data->window_height)
    {
        data->color_buffer[i] = color;
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
    init_buffer_image(data);
    generate_floor_cealing(data);
    generate_3d_walls(data);
    render_color_buffer(data);
    clear_color_buffer(data, 0x000000);
    render_map(data);
    render_ray(data);
    render_player(data); 
    mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->buffer_image.img, 0, 0);
    if (data->buffer_image.img)
        mlx_destroy_image(data->mlx_ptr, data->buffer_image.img);
}

int game_loop(t_data *data)
{
    if (!data->is_game_running)
        release_resources(data);
    update(data);
    render(data);
    return true;
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
        mlx_hook(data.mlx_win, ON_DESTROY, 1L << 17, release_resources, &data);
        mlx_loop(data.mlx_ptr);
    }
    
    release_resources(&data);
  
    
        
    return 0;
}

