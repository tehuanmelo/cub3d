/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-melo <tde-melo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:02:26 by tde-melo          #+#    #+#             */
/*   Updated: 2023/08/22 19:24:02 by tde-melo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_image	*get_textures(t_data *data)
{
	t_image	*textures;
	char	*north;
	char	*south;
	char	*east;
	char	*west;

	north = "textures/RED-BRICK.xpm";
	south = "textures/MOSS-ROCK.xpm";
	east = "textures/SILVER-ROCK.xpm";
	west = "textures/BLUE-ROCK.xpm";
	textures = malloc(sizeof(t_image) * 4);
	if (!textures)
		return (NULL);
	textures[0] = create_image(data, north);
	textures[1] = create_image(data, south);
	textures[2] = create_image(data, east);
	textures[3] = create_image(data, west);
	return (textures);
}
