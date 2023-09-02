/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoltay <mgoltay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:02:26 by tde-melo          #+#    #+#             */
/*   Updated: 2023/09/02 16:48:10 by mgoltay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_image	*get_textures(t_data *data)
{
	t_image	*textures;

	textures = malloc(sizeof(t_image) * 4); // NSEW
	if (!textures)
		return (NULL);
	textures[0] = create_image(data, "textures/RED-BRICK.xpm");
	textures[1] = create_image(data, "textures/MOSS-ROCK.xpm");
	textures[2] = create_image(data, "textures/SILVER-ROCK.xpm");
	textures[3] = create_image(data, "textures/BLUE-ROCK.xpm");
	return (textures);
}
